#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "pukan/common.hpp"
#include "pukan/math/math.hpp"

namespace json { class Object; }

namespace pukan {

class World;
class Body;
class Graphics;

class Entity : public sf::Drawable
{
public:
   Entity(Body * body, Graphics * graphics, const std::string & name = "");
   virtual ~Entity();

   virtual void update();
   virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;

   Body * getBody();
   const Body * getBody() const;
   Graphics * getGraphics();
   const Graphics * getGraphics() const;

   const std::string & getName() const;
   void setName(const std::string & name);

   Entity * clone() const;

   static Entity * fromJson(World * world, const json::Object & js);
   json::Object toJson() const;

private:
   Body * _body;
   Graphics * _graphics;

   std::string _name;
};

inline Body * Entity::getBody()
{
   assert(_body);
   return _body;
}

inline const Body * Entity::getBody() const
{
   assert(_body);
   return _body;
}

inline Graphics * Entity::getGraphics()
{
   assert(_graphics);
   return _graphics;
}

inline const Graphics * Entity::getGraphics() const
{
   assert(_graphics);
   return _graphics;
}

inline const std::string & Entity::getName() const
{
   return _name;
}

inline void Entity::setName(const std::string & name)
{
   _name = name;
}

}

#endif // ENTITY_HPP
