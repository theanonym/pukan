#ifndef WORLD_HPP
#define WORLD_HPP

#include "pukan/common.hpp"
#include "pukan/core/yobaobject.hpp"
#include "pukan/math/math.hpp"

namespace json { class Object; }

namespace pukan {

class Body;
class Entity;
class Joint;
class Fixture;
class BodyIterator;

class World : public YobaObject
{
   friend class ContactListener;
   friend class DestructionListener;

   typedef std::function<void ()> UpdateCallback;
   typedef std::function<void (b2Contact *)> CollisionCallback;
   typedef std::function<void (Fixture *)> DestructionCallback;

public:
   enum ContactType
   {
      BeginContact,
      EndContact,
      PreSolve,
      PostSolve
   };

   World(YobaObject * parent);
   ~World();

   void onUpdate();

   Body * createBody(bool isDynamic, const Vec2f & pos = Vec2f());

   bool createMouseJoint(const Vec2f & mousePos);
   void removeMouseJoint();
   b2MouseJoint * getMouseJoint() const;

   Body * findById(int id) const;
   Body * findFirstByPos(const Vec2f & pos) const;
   std::vector<Body *> findByRect(const Rectf & rect);
   Body * getLast() const;
   Entity * findFirstByName(const std::string & name);
   std::vector<Entity *> findByName(const std::string & name);

   BodyIterator getBodyIterator() const;

   int getLastId() const;
   int getNextId();

   void removeAll();

   void addUpdateCallback(UpdateCallback cb);
   void setCollisionCallback(ContactType stage,
                             CollisionCallback cb);
   void setDestructionCallback(DestructionCallback cb);

   void saveToFile(const bfs::path & path) const;
   void loadFromFile(const bfs::path & path, const Vec2f & posModifier);

//private:
   b2World * getB2World();
   const b2World * getB2World() const;

private:
   std::unique_ptr<b2World> _b2world;

   int _lastId = -1;

   CollisionCallback _beginContactCB;
   CollisionCallback _endContactCB;
   CollisionCallback _preSolveCB;
   CollisionCallback _postSolveCB;
   DestructionCallback _destructionCB;

   b2MouseJoint * _mouseJoint = nullptr;

   std::queue<UpdateCallback> _updateCallbacks;
};

inline b2World * World::getB2World()
{
   return _b2world.get();
}

inline const b2World * World::getB2World() const
{
   return _b2world.get();
}

}

#endif // WORLD_HPP
