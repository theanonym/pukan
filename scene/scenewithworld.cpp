#include "pukan/scene/scenewithworld.hpp"
#include "pukan/core/physics/world.hpp"

namespace pukan {

SceneWithWorld::SceneWithWorld(YobaObject * parent)
{
   _world = new World(parent);

   _world->setCollisionCallback(World::BeginContact,
                                [this] (b2Contact * b2contact)
                                { onBeginContact(b2contact); });
   _world->setCollisionCallback(World::EndContact,
                                [this] (b2Contact * b2contact)
                                { onEndContact(b2contact); });
   _world->setCollisionCallback(World::PreSolve,
                                [this] (b2Contact * b2contact)
                                { onPreSolveContact(b2contact); });
   _world->setCollisionCallback(World::PostSolve,
                                [this] (b2Contact * b2contact)
                                { onPostSolveContact(b2contact); });

   _world->setDestructionCallback([this] (Fixture * fixture)
                                  { onDestruction(fixture); });
}

SceneWithWorld::~SceneWithWorld()
{
}

void SceneWithWorld::drawB2Debug()
{
//   _world->drawB2Debug();
}

World * SceneWithWorld::getWorld()
{
   assert(_world);
   return _world;
}

const World * SceneWithWorld::getWorld() const
{
   assert(_world);
   return _world;
}

void SceneWithWorld::onBeginContact(b2Contact *)
{
}

void SceneWithWorld::onEndContact(b2Contact *)
{
}

void SceneWithWorld::onPreSolveContact(b2Contact *)
{
}

void SceneWithWorld::onPostSolveContact(b2Contact *)
{
}

void SceneWithWorld::onDestruction(Fixture *)
{
}

}
