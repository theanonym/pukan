#ifndef TEXT_HPP
#define TEXT_HPP

#include "pukan/common.hpp"
#include "pukan/gui/guielement.hpp"

namespace pukan {
namespace gui {

class Text : public Element
{
public:
   Text(const Vec2f & screenPos,
        bool posIsCenter,
        const sf::String & string,
        const sf::Font * font,
        const sf::Color & color,
        unsigned charSize);

   virtual void setScreenPos(const Vec2f & pos, bool center = true);
   virtual Recti getScreenBounds() const;

public:
   sf::Text * getText();
   const sf::Text * getText() const;

private:
   std::unique_ptr<sf::Text> _text;
};

} // ns gui
} // ns pukan

#endif // TEXT_HPP
