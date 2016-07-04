#include "pukan/core/physics/contactlistener.hpp"
#include "pukan/core/physics/world.hpp"

namespace pukan {

ContactListener::ContactListener(World * world)
   : _world(world)
{
}

void ContactListener::BeginContact(b2Contact * contact)
{
   if(_world->_beginContactCB)
      _world->_beginContactCB(contact);
}

void ContactListener::EndContact(b2Contact * contact)
{
   if(_world->_endContactCB)
      _world->_endContactCB(contact);
}

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
   YOBA_UNUSED(oldManifold);

   if(_world->_preSolveCB)
      _world->_preSolveCB(contact);
}

void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
   YOBA_UNUSED(impulse);

   if(_world->_postSolveCB)
      _world->_postSolveCB(contact);
}

}
