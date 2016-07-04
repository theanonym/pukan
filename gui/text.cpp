#include "pukan/gui/text.hpp"

namespace pukan {
namespace gui {

//todo setorigin
Text::Text(const Vec2f & screenPos,
           bool posIsCenter,
           const sf::String & string,
           const sf::Font * font,
           const sf::Color & color,
           unsigned charSize)
   : _text(nullptr)
{
   sf::Text * text = new sf::Text(string, *font, charSize);
   text->setColor(color);

   _text.reset(text);
   Element::setBaseObj(text);

   setScreenPos(screenPos, posIsCenter);
}

void Text::setScreenPos(const Vec2f & pos, bool center)
{
   if(!center)
   {
      Element::setScreenPos(Vec2f(pos.x,
                                    pos.y - getText()->getGlobalBounds().height / 2));
   }
   else
   {
      Element::setScreenPos(Vec2f(pos.x - getText()->getGlobalBounds().width / 2,
                                    pos.y - getText()->getGlobalBounds().height));
   }
}

Recti Text::getScreenBounds() const
{
   return Recti(getText()->getGlobalBounds());
}

const sf::Text * Text::getText() const
{
   assert(_text);
   return _text.get();
}

sf::Text *Text::getText()
{
   assert(_text);
   return _text.get();
}

} // ns gui
} // ns pukan
