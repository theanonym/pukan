#include "checkbox.hpp"

namespace pukan {
namespace gui {

CheckBox::CheckBox(const Vec2f & screenPos,
                   const Vec2f & size,
                   const sf::Color & fillColor,
                   const sf::Color & outlineColor,
                   int outlineWidth)
   : Rectangle(screenPos, size, fillColor, outlineColor, outlineWidth)
{
}

void CheckBox::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
   Rectangle::draw(renderTarget, renderStates);

   if(isChecked())
   {
      Vec2f size(getScreenPos().getDistanceTo(getScreenBounds().getBottomRight()) - 2, 3);
      sf::RectangleShape line(size);
      line.setFillColor(sf::Color(255, 226, 76));
      line.setOutlineColor(sf::Color::Black);
      line.setOutlineThickness(2);
      line.setPosition(getScreenBounds().getBottomLeft() + Vec2f(0, -1));
      line.setRotation(-45);
      renderTarget.draw(line);
      line.setPosition(getScreenPos() + Vec2f(2, -1));
      line.setRotation(45);
      renderTarget.draw(line);
   }
}

bool CheckBox::isChecked() const
{
   return _isChecked;
}

void CheckBox::setChecked(bool value)
{
   _isChecked = value;
}

} // ns gui
} // ns pukan
