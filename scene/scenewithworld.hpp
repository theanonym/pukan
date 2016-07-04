#ifndef SCENEWITHWORLD_HPP
#define SCENEWITHWORLD_HPP

#include "pukan/common.hpp"

namespace pukan {

class YobaObject;
class World;
class Fixture;

class SceneWithWorld
{
public:
   SceneWithWorld(YobaObject * parent);
   virtual ~SceneWithWorld();

   void drawB2Debug();

protected:
   World * getWorld();
   const World * getWorld() const;

   virtual void onBeginContact(b2Contact *);
   virtual void onEndContact(b2Contact *);
   virtual void onPreSolveContact(b2Contact *);
   virtual void onPostSolveContact(b2Contact *);
   virtual void onDestruction(Fixture *);

private:
   World * _world;
};

}

#endif // SCENEWITHWORLD_HPP
