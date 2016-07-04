#include "pukan/core/physics/destructionlistener.hpp"
#include "pukan/core/physics/world.hpp"

namespace pukan {

DestructionListener::DestructionListener(World * world)
   : _world(world)
{
}

void DestructionListener::SayGoodbye(b2Joint *)
{
}

void DestructionListener::SayGoodbye(b2Fixture * b2fixture)
{
   if(_world->_destructionCB)
      _world->_destructionCB(static_cast<Fixture *>(b2fixture->GetUserData()));


}

}
