#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "pukan/common.hpp"
#include "pukan/gui/guielement.hpp"

namespace pukan {
namespace gui {

class Rectangle : public Element
{
public:
   Rectangle(const Vec2f & screenPos,
             const Vec2f & size,
             const sf::Color & fillColor,
             const sf::Color & outlineColor = sf::Color(),
             int outlineWidth = 0);

   virtual Recti getScreenBounds() const;

public:
   sf::RectangleShape * getShape();
   const sf::RectangleShape * getShape() const;

private:
   std::unique_ptr<sf::RectangleShape> _shape;
};

} // ns gui
} // ns pukan

#endif // RECTANGLE_HPP
