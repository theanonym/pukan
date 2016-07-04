#include "material.hpp"

namespace pukan {

Material::Material()
{
}

Material::Material(const std::string & textureName,
                   const Physics & physics)
   : _textureName(textureName),
     _physics(physics)
{
}

const std::string & Material::getTextureName() const
{
   return _textureName;
}

const Physics & Material::getPhysics() const
{
   return _physics;
}

bool Material::operator==(const Material & other) const
{
   return _textureName == other._textureName &&
          _physics == other._physics;
}

}
