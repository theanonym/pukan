#ifndef BODY_HPP
#define BODY_HPP

#include "pukan/common.hpp"
#include "pukan/core/temporary.hpp"
#include "pukan/math/math.hpp"
#include "pukan/core/physics/physics.hpp"

namespace json { class Object; }

namespace pukan {

class World;
class Fixture;
class Entity;

/*
 * Обёртка для b2Body
 *
 * Засовывается в b2Body::SetUserData().
 *
 */
class Body : public Temporary
{
   friend class World;
   friend class Entity;
   friend std::ostream & operator << (std::ostream &, const Body &);

public:
   Body(World * world, bool isDynamic, const Vec2f & pos = Vec2f());
   Body(const Body & copy) = delete;
   virtual ~Body();

   Fixture * createPolygonFixture(const std::vector<Vec2f> & points,
                                  const Physics & physics = Physics());

   Fixture * createCircleFixture(float radius,
                                 const Physics & physics = Physics());

   Fixture * createRectangleFixture(const Vec2f & size,
                                    const Physics & physics = Physics());

   int getId() const;
   bool isDynamic() const;
   void setDynamic(bool dynamic);

   Vec2f getPos(bool center = true) const;
   void setPos(float x, float y, bool center = true);
   void setPos(const Vec2f & pos, bool center = true);
   float getAngle() const;
   void setAngle(float degrees);
   Vec2f getLinearVelocity() const;
   void setLinearVelocity(const Vec2f & velocity);

   Rectf getAABB() const;
   b2AABB getB2AABB() const;

   static Body * fromJson(World * world, const json::Object & jobj);
   json::Object toJson() const;

//protected:
   World * getWorld() const;

   Entity * getEntity();
   const Entity * getEntity() const;

   const std::vector<std::unique_ptr<Fixture>> & getFixtureList() const;
   unsigned getFixtureCount() const;
   Fixture * getFirstFixture() const;
   Fixture * getLastFixture() const;

   b2Body * getB2Body();
   const b2Body * getB2Body() const;

   operator std::string() const;

private:
   Fixture * createFixture(b2Shape * b2shape, const Physics & physics);

   void saveEntity(Entity * entity);

private:
   World * _world;

   int  _id = -1;
   bool _isDynamic = false;

   b2Body * _b2body = nullptr;
   Entity * _entity;

   std::vector<std::unique_ptr<Fixture>> _fixtures;
};

inline Entity * Body::getEntity()
{
   assert(_entity);
   return _entity;
}

inline const Entity * Body::getEntity() const
{
   assert(_entity);
   return _entity;
}

inline const std::vector<std::unique_ptr<Fixture> > & Body::getFixtureList() const
{
   return _fixtures;
}

inline unsigned Body::getFixtureCount() const
{
   return _fixtures.size();
}

inline Fixture * Body::getFirstFixture() const
{
   return getFixtureList().front().get();
}

inline Fixture * Body::getLastFixture() const
{
   return getFixtureList().back().get();
}

inline b2Body * Body::getB2Body()
{
   return _b2body;
}

inline const b2Body * Body::getB2Body() const
{
   return _b2body;
}

}

#endif // BODY_HPP
