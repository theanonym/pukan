#include "pukan/core/physics/fixture.hpp"
#include "json/jobject.hpp"

namespace pukan {

Fixture::Fixture(b2Fixture * b2fixture)
   : _b2fixture(b2fixture)
{
   b2fixture->SetUserData(static_cast<void *>(this));

   setFilter(Filter());
}

Body * Fixture::getBody()
{
   return static_cast<Body *>(getB2Fixture()->GetBody()->GetUserData());
}

const Body * Fixture::getBody() const
{
   return static_cast<const Body *>(getB2Fixture()->GetBody()->GetUserData());
}

Fixture::Shape Fixture::getShape() const
{
   return _shape;
}

const Physics & Fixture::getPhysics() const
{
   return _physics;
}

const std::vector<Vec2f> Fixture::getPolygonVertices() const
{
   assert(getShape() == Polygon);
   return _polygonVertices;
}

const Vec2f & Fixture::getRectangleSize() const
{
   assert(getShape() == Rectangle);
   return _rectangleSize;
}

float Fixture::getCircleRadius() const
{
   assert(getShape() == Circle);
   return _circleRadius;
}

bool Fixture::isSensor() const
{
   return getB2Fixture()->IsSensor();
}

void Fixture::setSensor(bool value)
{
   getB2Fixture()->SetSensor(value);
}

Filter Fixture::getFilter() const
{
   return Filter::fromB2Filter(getB2Fixture()->GetFilterData());
}

void Fixture::setFilter(const Filter & filter)
{
   getB2Fixture()->SetFilterData(filter.toB2Filter());
}

b2Fixture * Fixture::getB2Fixture()
{
   assert(_b2fixture);
   return _b2fixture;
}

const b2Fixture * Fixture::getB2Fixture() const
{
   assert(_b2fixture);
   return _b2fixture;
}

const b2Shape * Fixture::getB2Shape() const
{
   return getB2Fixture()->GetShape();
}

void Fixture::saveShape(Fixture::Shape shape)
{
   _shape = shape;
}

void Fixture::savePhysics(const Physics & physics)
{
   _physics = physics;
}

void Fixture::savePolygonVertices(const std::vector<Vec2f> & points)
{
   _polygonVertices = points;
}

void Fixture::saveRectangleSize(const Vec2f & size)
{
   _rectangleSize = size;
}

void Fixture::saveCircleRadius(float radius)
{
   _circleRadius = radius;
}

json::Object Fixture::toJson() const
{
   json::Object jfixture(json::Object::Hash);

   // shape
   jfixture.add("shape", static_cast<int>(getShape()));


   // polygonVertices/rectangleSize/circleRadius
   switch(getShape())
   {
      case Polygon:
      {
         json::Object jpoints(json::Object::Array);
         for(const Vec2f & point : getPolygonVertices())
            jpoints.add(point.toJson());
         jfixture.add("polygonVertices", jpoints);
      } break;

      case Rectangle:
         jfixture.add("rectangleSize", getRectangleSize().toJson());
         break;

      case Circle:
         jfixture.add("circleRadius", getCircleRadius());
         break;
   }

   // physics
   jfixture.add("physics", getPhysics().toJson());

   // isSensor
   jfixture.add("isSensor", getB2Fixture()->IsSensor());

   // Фильтер
   jfixture.add("filter", getFilter().toJson());

   return jfixture;
}

}
