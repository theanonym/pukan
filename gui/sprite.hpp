#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "pukan/common.hpp"
#include "pukan/gui/guielement.hpp"

namespace pukan {
namespace gui {

class Sprite : public Element
{
public:
   Sprite(const Vec2f & screenPos,
          bool posIsCenter,
          const sf::Texture * texture,
          const Vec2f & spriteScale = Vec2f(),
          const Recti & textureRect = Recti());

   virtual Recti getScreenBounds() const;

public:
   sf::Sprite * getSprite();
   const sf::Sprite * getSprite() const;

private:
   std::unique_ptr<sf::Sprite> _sprite;
};

} // ns gui
} // ns pukan
#endif // SPRITE_HPP
