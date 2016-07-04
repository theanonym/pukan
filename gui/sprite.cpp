#include "pukan/gui/sprite.hpp"

namespace pukan {
namespace gui {

Sprite::Sprite(const Vec2f & screenPos,
               bool posIsCenter,
               const sf::Texture * texture,
               const Vec2f & spriteScale,
               const Recti & textureRect)
   : _sprite(nullptr)
{
   sf::Sprite * sprite = new sf::Sprite(*texture);
   if(posIsCenter)
      sprite->setOrigin(sprite->getGlobalBounds().width  / 2.f,
                        sprite->getGlobalBounds().height / 2.f);

   if(spriteScale != Vec2f())
      sprite->setScale(spriteScale.x,
                       spriteScale.y);

   if(textureRect != Recti())
      sprite->setTextureRect(textureRect);

   sprite->setPosition(screenPos);
   _sprite.reset(sprite);
   Element::setBaseObj(sprite);
}

Recti Sprite::getScreenBounds() const
{
   return Recti(getSprite()->getGlobalBounds());
}

const sf::Sprite * Sprite::getSprite() const
{
   assert(_sprite);
   return _sprite.get();
}

sf::Sprite * Sprite::getSprite()
{
   assert(_sprite);
   return _sprite.get();
}

} // ns gui
} // ns pukan
