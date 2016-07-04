#ifndef INDICATOR_HPP
#define INDICATOR_HPP

#include "pukan/common.hpp"
#include "pukan/gui/rectangle.hpp"

namespace pukan {
namespace gui {

class Indicator : public Rectangle
{
public:
   Indicator(const Vec2f & screenPos,
             const Vec2f & maxSize,
             const sf::Color & fillColor);

   void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const;

   float getFactor() const;
   void setFactor(float factor);

private:
   float _factor = 0;
};

} // ns gui
} // ns pukan

#endif // INDICATOR_HPP
