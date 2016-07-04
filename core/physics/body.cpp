#include "pukan/core/physics/body.hpp"
#include "pukan/core/physics/fixture.hpp"
#include "pukan/core/physics/world.hpp"
#include "pukan/core/services/logger.hpp"
#include "json/jobject.hpp"

namespace pukan {

Body::Body(World * world, bool isDynamic, const Vec2f & pos)
   : _world(world),
     _id(world->getNextId()),
     _isDynamic(isDynamic)
{
   b2BodyDef bodyDef;
   bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
   if(pos != Vec2f())
      bodyDef.position = pos.toB2Pos();

   b2Body * b2body = world->getB2World()->CreateBody(&bodyDef);
   b2body->SetUserData(static_cast<void *>(this));
   _b2body = b2body;

//   Logger::get().debug("Body created: %1%") << *this;
}

Body::~Body()
{
   getB2Body()->GetWorld()->DestroyBody(getB2Body());
}

Fixture * Body::createPolygonFixture(const std::vector<Vec2f> & points,
                                     const Physics & physics)
{
   b2PolygonShape b2shape;
   b2Vec2 * b2points = new b2Vec2[points.size()];
   for(unsigned i = 0; i < points.size(); i++)
      b2points[i] = points[i].toB2Pos();
   b2shape.Set(b2points, points.size());
   delete [] b2points;

   Fixture * fixture = createFixture(&b2shape, physics);
   fixture->saveShape(Fixture::Polygon);
   fixture->savePhysics(physics);
   fixture->savePolygonVertices(points);
   return fixture;
}

Fixture * Body::createCircleFixture(float radius,
                                    const Physics & physics)
{
   b2CircleShape b2shape;
   b2shape.m_radius = Vec2f(radius, 0).toB2Size().x;

   Fixture * fixture = createFixture(&b2shape, physics);
   fixture->saveShape(Fixture::Circle);
   fixture->savePhysics(physics);
   fixture->saveCircleRadius(radius);
   return fixture;
}

Fixture * Body::createRectangleFixture(const Vec2f & size,
                                       const Physics & physics)
{
   std::vector<Vec2f> polygonPoints {
      Vec2f(-size.x / 2, -size.y / 2), Vec2f(+size.x / 2, -size.y / 2),
      Vec2f(+size.x / 2, +size.y / 2), Vec2f(-size.x / 2, +size.y / 2)
   };

   Fixture * fixture = createPolygonFixture(polygonPoints, physics);
   fixture->saveShape(Fixture::Rectangle);
   fixture->savePhysics(physics);
   fixture->saveRectangleSize(size);
   return fixture;
}

int Body::getId() const
{
   return _id;
}

bool Body::isDynamic() const
{
   return _isDynamic;
}

void Body::setDynamic(bool dynamic)
{
   _isDynamic = dynamic;
   if(dynamic && getB2Body()->GetType() != b2_dynamicBody)
      getB2Body()->SetType(b2_dynamicBody);
}

Vec2f Body::getPos(bool center) const
{
   if(center)
   {
      return Vec2f::fromB2Pos(getB2Body()->GetPosition());
   }
   else
   {
      Fixture * fixture =
            static_cast<Fixture *>(getB2Body()->GetFixtureList()->GetUserData());
      assert(fixture->getShape() != Fixture::Polygon);
      return getAABB().getPos();
   }
}

void Body::setPos(float x, float y, bool center)
{
   setPos(Vec2f(x, y), center);
}

void Body::setPos(const Vec2f & pos, bool center)
{
   if(center)
   {
      getB2Body()->SetTransform(pos.toB2Pos(), getB2Body()->GetAngle());
   }
   else
   {
      // Найти левый верхний угол - нетривиальная задача
      Fixture * fixture = getFixtureList().back().get();
      switch(fixture->getShape())
      {
         case Fixture::Rectangle:
            setPos(pos + fixture->getRectangleSize() / 2.f);
            return;

         default: throw;
      }
   }
}

float Body::getAngle() const
{
   return -radiansToDegrees(getB2Body()->GetAngle());
}

void Body::setAngle(float degrees)
{
   getB2Body()->SetTransform(getB2Body()->GetTransform().p, -degreesToRadians(degrees));
}

Vec2f Body::getLinearVelocity() const
{
   return Vec2f::fromB2Vec(getB2Body()->GetLinearVelocity());
}

void Body::setLinearVelocity(const Vec2f & velocity)
{
   getB2Body()->SetLinearVelocity(velocity.toB2Vec());
}

Rectf Body::getAABB() const
{
   assert(getFixtureCount());

   return Rectf::fromB2AABB(getB2AABB());
}

b2AABB Body::getB2AABB() const
{
   assert(getFixtureCount());

   b2AABB aabb;
   aabb.lowerBound.Set( FLT_MAX,  FLT_MAX);
   aabb.upperBound.Set(-FLT_MAX, -FLT_MAX);

   for(const b2Fixture * node = getB2Body()->GetFixtureList(); node; node = node->GetNext())
      aabb.Combine(aabb, node->GetAABB(0));

   assert(aabb.lowerBound.x !=  FLT_MAX);
   assert(aabb.lowerBound.y !=  FLT_MAX);
   assert(aabb.upperBound.x != -FLT_MAX);
   assert(aabb.upperBound.y != -FLT_MAX);

   return aabb;
}

Body * Body::fromJson(World * world, const json::Object & jobj)
{
   Body * body = new Body(world,
                          jobj.get<bool>("isDynamic"),
                          Vec2f::fromJson(jobj.get("pos")));
   body->setAngle(jobj.get<float>("angle"));

   for(const json::Object & jfixture : jobj.get("fixtures").getArray())
   {
      Physics physics = Physics::fromJson(jfixture.get("physics"));

      Fixture * fixture = nullptr;
      switch(static_cast<Fixture::Shape>(jfixture.get<int>("shape")))
      {
         case Fixture::Polygon:
         {
            std::vector<Vec2f> vertices;
            for(const json::Object & jpoint : jfixture.get("polygonVertices").getArray())
               vertices.push_back(Vec2f::fromJson(jpoint));

            fixture = body->createPolygonFixture(vertices, physics);
            break;
         }

         case Fixture::Rectangle:
            fixture = body->createRectangleFixture(Vec2f::fromJson(jfixture.get("rectangleSize")),
                                                   physics);
            break;

         case Fixture::Circle:
            fixture = body->createCircleFixture(jfixture.get<float>("circleRadius"),
                                                physics);
            break;
      }

      fixture->getB2Fixture()->SetSensor(jfixture.get<bool>("isSensor"));

      fixture->setFilter(Filter::fromJson(jfixture.get("filter")));
   }

   return body;
}

json::Object Body::toJson() const
{
   json::Object jbody(json::Object::Hash);

   // id
   jbody.add("id", getId());

   // isDynamic
   jbody.add("isDynamic", isDynamic());

   // pos
   jbody.add("pos", getPos().toJson());

   // angle
   jbody.add("angle", getAngle());

   // fixtures
   json::Object jfixtures(json::Object::Array);
   for(const std::unique_ptr<Fixture> & fixture : getFixtureList())
      jfixtures.add(fixture->toJson());
   jbody.add("fixtures", jfixtures);

   return jbody;
}

World * Body::getWorld() const
{
   return _world;
}

Fixture * Body::createFixture(b2Shape * b2shape, const Physics & physics)
{   
   b2Fixture * b2fixture = nullptr;
   if(physics)
   {
      b2FixtureDef b2fd;
      b2fd.density     = physics.density;
      b2fd.friction    = physics.friction;
      b2fd.restitution = physics.restitution;

      b2fd.shape = b2shape;

      b2fixture = getB2Body()->CreateFixture(&b2fd);
   }
   else
   {
      b2fixture = getB2Body()->CreateFixture(b2shape, 1);
   }

   Fixture * fixture = new Fixture(b2fixture);
   _fixtures.push_back(std::unique_ptr<Fixture>(fixture));
   return fixture;
}

void Body::saveEntity(Entity * entity)
{
   assert(entity);
   _entity = entity;
}

Body::operator std::string() const
{
   return (b::format("Body(\n"
                     "   id: %1%\n"
                     "   Dynamic: %2%\n"
                     "   Main shape: %3%\n"
                     "   Fixtures: %4%\n"
                     "   Game pos: %5%,\n"
                     "   Box2D mass: %6%)")
           % getId()
           % boost::io::group(std::boolalpha, isDynamic())
           % (getFixtureCount() ? getFirstFixture()->getShape() : 0)
           % getFixtureCount()
           % std::string(getPos())
           % getB2Body()->GetMass()).str();
}

}
