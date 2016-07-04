#ifndef DESTRUCTIONLISTENER_HPP
#define DESTRUCTIONLISTENER_HPP

#include "pukan/common.hpp"

namespace pukan {

class World;

class DestructionListener : public b2DestructionListener
{
public:
   DestructionListener(World * world);

   void SayGoodbye(b2Joint * joint);
   void SayGoodbye(b2Fixture * b2fixture);

private:
   World * _world;
};

}

#endif // DESTRUCTIONLISTENER_HPP
