#ifndef PHYSICS_HPP
#define PHYSICS_HPP

/*
 * http://engineeringtoolbox.com/density-solids-d_1265.html
 * http://engineershandbook.com/Tables/frictioncoefficients.htm
 * http://hypertextbook.com/facts/2006/restitution.shtml
 */

#include "pukan/common.hpp"

namespace json { class Object; }

namespace pukan {

struct Physics
{
   float density = 0;
   float friction = 0;
   float restitution = 0;

   Physics();
   Physics(float d, float f, float r);

   bool operator==(const Physics & other) const;
   operator bool() const;

   static Physics fromJson(const json::Object & jobj);
   json::Object toJson() const;
};

}

#endif // PHYSICS_HPP
