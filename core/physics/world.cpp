#include "pukan/core/physics/world.hpp"
#include "pukan/core/physics/body.hpp"
#include "pukan/core/physics/fixture.hpp"
#include "pukan/core/physics/contactlistener.hpp"
#include "pukan/core/physics/destructionlistener.hpp"
#include "pukan/core/physics/worldquerry.hpp"
#include "pukan/core/physics/bodyiterator.hpp"
#include "pukan/core/graphics/graphics.hpp"
#include "pukan/core/services/config.hpp"
#include "pukan/core/services/resources.hpp"
#include "pukan/core/services/logger.hpp"
#include "pukan/core/entity.hpp"
#include "json/jparser.hpp"
#include "json/jobject.hpp"
#include "pukan/math/math.hpp"

namespace pukan {

World::World(YobaObject * parent)
   : YobaObject(parent)
{
   _b2world.reset(new b2World(b2Vec2(0, -10)));

   getB2World()->SetAllowSleeping(true);
   getB2World()->SetContactListener(new ContactListener(this));
   getB2World()->SetDestructionListener(new DestructionListener(this));
}

World::~World()
{
}

void World::onUpdate()
{


   getB2World()->Step(Config::get().gameSpeed / Config::get().fpsLimit,
                      int(8 * Config::get().physicsAccuracy),
                      int(3 * Config::get().physicsAccuracy));

   while(!_updateCallbacks.empty())
   {
      _updateCallbacks.front()();
      _updateCallbacks.pop();
   }

   for(auto it = getBodyIterator(); it; it++)
      it.get()->getEntity()->update();


   b2Body * node = getB2World()->GetBodyList();
   while(node)
   {
      b2Body * b2body = node;
      node = node->GetNext();

      Body * body = static_cast<Body *>(b2body->GetUserData());
      if(body->needToRemove())
         delete body->getEntity();
   }
}

Body * World::createBody(bool isDynamic, const Vec2f & pos)
{
   return new Body(this, isDynamic, pos);
}

bool World::createMouseJoint(const Vec2f & mousePos)
{
   Body * body = findFirstByPos(mousePos);
   if(body == nullptr || body->getId() == 1 || !body->isDynamic())
      return false;

   body->getB2Body()->SetAwake(true);

   b2MouseJointDef jd;
   jd.bodyA = findById(1)->getB2Body(); // Не используется
   jd.bodyB = body->getB2Body();
   jd.target = mousePos.toB2Pos();
   jd.collideConnected = true;
   jd.maxForce = body->getB2Body()->GetMass() * 1000;

   _mouseJoint = static_cast<b2MouseJoint *>(getB2World()->CreateJoint(&jd));

   return true;
}

void World::removeMouseJoint()
{
   if(_mouseJoint)
   {
      // Некоторая защита от сегфолта.
      // if(_mouseJoint) и if(_mouseJoint->GetBodyB()) не работает.
      if(getB2World()->GetJointCount())
         getB2World()->DestroyJoint(_mouseJoint);
      _mouseJoint = nullptr;
   }
}

b2MouseJoint * World::getMouseJoint() const
{
   return _mouseJoint;
}

Body * World::findById(int id) const
{
   for(const b2Body * b2ody = getB2World()->GetBodyList(); b2ody; b2ody = b2ody->GetNext())
   {
      Body * body = static_cast<Body *>(b2ody->GetUserData());
      if(body->getId() == id)
         return body;
   }

   ythrow(std::runtime_error, "ID " << id << " не найден.");
}

Body * World::findFirstByPos(const Vec2f & pos) const
{
   b2AABB aabb;
   aabb.lowerBound = pos.toB2Pos();
   aabb.upperBound = pos(0, 1).toB2Pos();

   WorldQuerry querry;
   getB2World()->QueryAABB(&querry, aabb);

   if(!querry.isEmpty())
      return querry.getFirst();
   else
      return nullptr;
}

std::vector<Body *> World::findByRect(const Rectf & rect)
{
   b2AABB aabb;
   aabb.lowerBound = Vec2f(rect.x, rect.y + rect.h).toB2Pos(); // Левый нижний
   aabb.upperBound = Vec2f(rect.x + rect.w, rect.y).toB2Pos();  // Правый верхний

   WorldQuerry querry;
   getB2World()->QueryAABB(&querry, aabb);

   return querry.getList();
}

Body * World::getLast() const
{
   const b2Body * node = getB2World()->GetBodyList();
   assert(node);
   return static_cast<Body *>(node->GetUserData());
}

Entity * World::findFirstByName(const std::string & name)
{
   for(auto it = getBodyIterator(); it; it++)
      if(it.get()->getEntity()->getName() == name)
         return it.get()->getEntity();
   ythrow(std::runtime_error, "Предмет с именем `"<< name << "'не найден.");
   return nullptr;
}

std::vector<Entity *> World::findByName(const std::string & name)
{
   std::vector<Entity *> result;
   for(auto it = getBodyIterator(); it; it++)
      if(it.get()->getEntity()->getName() == name)
         result.push_back(it.get()->getEntity());
   return result;
}

BodyIterator World::getBodyIterator() const
{
   return BodyIterator(getB2World()->GetBodyList(),
                       getB2World()->GetBodyCount());
}

int World::getLastId() const
{
   return _lastId;
}

int World::getNextId()
{
   return ++_lastId;
}

void World::removeAll()
{
   for(auto it = getBodyIterator(); it; it++)
      delete it.get()->getEntity();
   _lastId = -1;
}

void World::addUpdateCallback(World::UpdateCallback cb)
{
   _updateCallbacks.push(cb);
}

void World::setCollisionCallback(World::ContactType stage,
                                 World::CollisionCallback cb)
{
   switch(stage)
   {
      case BeginContact: _beginContactCB = cb; break;
      case EndContact:   _endContactCB = cb; break;
      case PreSolve:     _preSolveCB = cb; break;
      case PostSolve:    _postSolveCB = cb; break;
   }
}

void World::setDestructionCallback(World::DestructionCallback cb)
{
   _destructionCB = cb;
}

void World::saveToFile(const bfs::path & path) const
{
   Logger::get().debug("Сохранение объектов в файл %1%") % path.string();

   json::Object jworld(json::Object::Hash);

   // Local rect
   {
      b2AABB combinedAABB;
      combinedAABB.lowerBound.Set( FLT_MAX,  FLT_MAX);
      combinedAABB.upperBound.Set(-FLT_MAX, -FLT_MAX);
      for(const b2Body * b2body = getB2World()->GetBodyList(); b2body; b2body = b2body->GetNext())
      {
         const Body * body = static_cast<const Body *>(b2body->GetUserData());
         if(body->isDynamic())
            combinedAABB.Combine(body->getB2AABB());
      }
      jworld.add("aabb", Rectf::fromB2AABB(combinedAABB).toJson());
   }

   // Bodies
   {
      json::Object jentities(json::Object::Array);
      for(auto it = getBodyIterator(); it; ++it)
         if(it.get()->isDynamic())
            jentities.add(it.get()->getEntity()->toJson());

      jworld.add("entities", std::move(jentities));
   }

   std::ofstream file(path.string());
   assert(file.good());
   file << std::move(jworld.toString(false));
}

void World::loadFromFile(const bfs::path & path, const Vec2f & posModifier)
{
   Logger::get().debug("Загрузка объектов из файла %1%") % path.string();

   json::Parser jparser;
   jparser.readFile(path.string());
   const json::Object & jroot = jparser.getRoot();

   // Local rect
   Rectf aabb = Rectf::fromJson(jroot.get("aabb"));

   // Entities
   for(const json::Object & jentity : jroot.get("entities").getArray())
   {
      Entity * entity = Entity::fromJson(this, jentity);
      entity->getBody()->setPos(
               entity->getBody()->getPos() + Vec2f(-aabb.x + posModifier.x,
                                                   -aabb.y + posModifier.y));
   }
}

}
