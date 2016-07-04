#include "pukan/gui/simplebutton.hpp"

namespace pukan {
namespace gui {

SimpleButton::SimpleButton(const Vec2f & screenPos,
                           const Vec2f & size,
                           const sf::Color & fillColor,
                           const sf::Color & outlineColor,
                           int outlineWidth,
                           const sf::String & string,
                           const sf::Font * font,
                           const sf::Color & color,
                           unsigned charSize)
   : _rect(new Rectangle(screenPos, size, fillColor, outlineColor, outlineWidth)),
     _text(new Text(Rectf(screenPos, size).getCenter(), true, string, font, color, charSize))
{
}

void SimpleButton::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
   _rect->draw(renderTarget, renderStates);
   _text->draw(renderTarget, renderStates);
}

Vec2f SimpleButton::getScreenPos() const
{
   return _rect->getScreenPos();
}

void SimpleButton::setScreenPos(const Vec2f & pos, bool center)
{
   _rect->setScreenPos(pos, center);
   _text->setScreenPos(_rect->getScreenBounds().getCenter(), true);
}

Recti SimpleButton::getScreenBounds() const
{
   return _rect->getScreenBounds();
}

Rectangle * SimpleButton::getRectangle() const
{
   return _rect.get();
}

Text * SimpleButton::getText() const
{
   return _text.get();
}

} // ns gui
} // ns pukan
