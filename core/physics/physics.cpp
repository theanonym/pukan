#include "pukan/core/physics/physics.hpp"
#include "json/jobject.hpp"

namespace pukan {

Physics::Physics()
{
}

Physics::Physics(float d, float f, float r)
   : density(d), friction(f), restitution(r)
{
}

bool Physics::operator==(const Physics & other) const
{
   return density == other.density &&
          friction == other.friction &&
          restitution == other.restitution;
}

Physics::operator bool() const
{
   return density && friction && restitution;
}

Physics Physics::fromJson(const json::Object & jobj)
{
   return Physics(jobj.get<float>("density"),
                  jobj.get<float>("friction"),
                  jobj.get<float>("restitution"));
}

json::Object Physics::toJson() const
{
   json::Object jphysics(json::Object::Hash);
   jphysics.add("density", density);
   jphysics.add("friction", friction);
   jphysics.add("restitution", restitution);
   return jphysics;
}

}
