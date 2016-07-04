#include "pukan/gui/indicator.hpp"

namespace pukan {
namespace gui {

Indicator::Indicator(const Vec2f & screenPos,
                     const Vec2f & maxSize,
                     const sf::Color & fillColor)
   : Rectangle(screenPos, maxSize, fillColor)
{
}

void Indicator::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
   sf::RectangleShape * shape = const_cast<sf::RectangleShape *>(getShape());

   Vec2f originalSize = shape->getSize();
   shape->setSize(Vec2f(originalSize.x * _factor + (_factor >= 0 ? 0 : 2),
                       originalSize.y));
   Rectangle::draw(renderTarget, renderStates);
   shape->setSize(originalSize);
}

float Indicator::getFactor() const
{
   return _factor;
}

void Indicator::setFactor(float factor)
{
   _factor = factor;
}

} // ns gui
} // ns pukan
