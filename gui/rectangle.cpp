#include "pukan/gui/rectangle.hpp"

namespace pukan {
namespace gui {

Rectangle::Rectangle(const Vec2f & screenPos,
                     const Vec2f & size,
                     const sf::Color & fillColor,
                     const sf::Color & outlineColor,
                     int outlineWidth)
   : _shape(nullptr)
{
   sf::RectangleShape * rs = new sf::RectangleShape;
   rs->setPosition(screenPos);
   rs->setSize(size);
   rs->setFillColor(fillColor);

   if(outlineWidth != 0)
   {
      rs->setOutlineColor(outlineColor);
      rs->setOutlineThickness(outlineWidth);
   }

   _shape.reset(rs);
   Element::setBaseObj(rs);
}

Recti Rectangle::getScreenBounds() const
{
   return Recti(getShape()->getGlobalBounds());
}

const sf::RectangleShape * Rectangle::getShape() const
{
   assert(_shape);
   return _shape.get();
}

sf::RectangleShape * Rectangle::getShape()
{
   assert(_shape);
   return _shape.get();
}

} // ns gui
} // ns pukan
