#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "pukan/common.hpp"
#include "pukan/gui/rectangle.hpp"

namespace pukan {
namespace gui {

class CheckBox : public Rectangle
{
public:
   CheckBox(const Vec2f & screenPos,
            const Vec2f & size,
            const sf::Color & fillColor,
            const sf::Color & outlineColor = sf::Color(),
            int outlineWidth = 0);

   void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const;

   bool isChecked() const;
   void setChecked(bool value);

private:
   bool _isChecked = true;
};

} // ns gui
} // ns pukan

#endif // CHECKBOX_HPP
