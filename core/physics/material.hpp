#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "pukan/common.hpp"
#include "pukan/core/physics/physics.hpp"

namespace pukan {

class Material
{
public:
   Material();

   Material(const std::string & textureName,
            const Physics & physics);

   const std::string & getTextureName() const;
   const Physics & getPhysics() const;

   bool operator==(const Material & other) const;

private:
   std::string _textureName;
   Physics _physics;
};

}

#endif // MATERIAL_HPP
