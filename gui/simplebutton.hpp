#ifndef SIMPLEBUTTON_HPP
#define SIMPLEBUTTON_HPP

#include "pukan/common.hpp"
#include "pukan/gui/guielement.hpp"
#include "pukan/gui/rectangle.hpp"
#include "pukan/gui/text.hpp"

namespace pukan {
namespace gui {

class Rectangle;
class Text;

class SimpleButton : public Element
{
public:
   SimpleButton(const Vec2f & screenPos,
                const Vec2f & size,
                const sf::Color & fillColor,
                const sf::Color & outlineColor,
                int outlineWidth,
                const sf::String & string,
                const sf::Font * font,
                const sf::Color & color,
                unsigned charSize);

   virtual void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const;

   virtual Vec2f getScreenPos() const;
   virtual void setScreenPos(const Vec2f & pos, bool center = false);
   virtual Recti getScreenBounds() const;

public:
   Rectangle * getRectangle() const;
   Text * getText() const;

private:
   std::unique_ptr<Rectangle> _rect;
   std::unique_ptr<Text>      _text;
};

} // ns gui
} // ns pukan

#endif // SIMPLEBUTTON_HPP
