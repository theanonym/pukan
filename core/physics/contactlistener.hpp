#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP

#include "pukan/common.hpp"

namespace pukan {

class World;

class ContactListener : public b2ContactListener
{
public:
   ContactListener(World * world);

   /// Called when two fixtures begin to touch.
   void BeginContact(b2Contact * contact);

   /// Called when two fixtures cease to touch.
   void EndContact(b2Contact * contact);

   /// This is called after a contact is updated. This allows you to inspect a
   /// contact before it goes to the solver. If you are careful, you can modify the
   /// contact manifold (e.g. disable contact).
   /// A copy of the old manifold is provided so that you can detect changes.
   /// Note: this is called only for awake bodies.
   /// Note: this is called even when the number of contact points is zero.
   /// Note: this is not called for sensors.
   /// Note: if you set the number of contact points to zero, you will not
   /// get an EndContact callback. However, you may get a BeginContact callback
   /// the next step.
   void PreSolve(b2Contact * contact, const b2Manifold * oldManifold);

   /// This lets you inspect a contact after the solver is finished. This is useful
   /// for inspecting impulses.
   /// Note: the contact manifold does not include time of impact impulses, which can be
   /// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
   /// in a separate data structure.
   /// Note: this is only called for contacts that are touching, solid, and awake.
   void PostSolve(b2Contact * contact, const b2ContactImpulse * impulse);

private:
   World * _world = nullptr;
};

}

#endif // CONTACTLISTENER_HPP
