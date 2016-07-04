#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "pukan/common.hpp"
#include "pukan/core/temporary.hpp"
#include "pukan/math/math.hpp"

namespace pukan {
namespace gui {

class Element : public Temporary, public sf::Drawable
{
   // GUI теребит onMouseClick() и onMouseMove()
   friend class GUI;

   typedef std::unique_ptr<Element> Ptr;
   typedef std::pair<std::string, Ptr> Pair;
   typedef std::function<void ()> MouseClickCallback;
   typedef std::function<void ()> MouseMoveCallback;

public:
   Element();
   Element(const Element & copy) = delete;

   bool isActive() const;
   void setActive(bool active);
   bool isMouseOver() const;

   void setMouseClickCallback(MouseClickCallback callback);
   void setMouseOverCallback(MouseMoveCallback callback);
   void setMouseOutCallback(MouseMoveCallback callback);

   virtual void update();
   virtual void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const;

   virtual Vec2f getScreenPos() const;
   virtual void setScreenPos(const Vec2f & pos, bool center = false);
   virtual Recti getScreenBounds() const = 0;

protected:
   template<typename T>
   void setBaseObj(T * sfmlObj)
   {
      _tranformable = dynamic_cast<sf::Transformable*>(sfmlObj);
      _drawable = dynamic_cast<sf::Drawable*>(sfmlObj);
   }

private:
   // Для GUI
   bool onMouseClick(const Vec2i & pos);
   void onMouseMove(const Vec2i & pos);

private:
   bool _isActive = true;
   bool _isMouseOver = false;

   bool _hasMouseclickCallback = false;
   bool _hasMouseMoveCallback  = false;

   MouseClickCallback _mouseClickCallback;
   MouseMoveCallback  _mouseOverCallback;
   MouseMoveCallback  _mouseOutCallback;

   sf::Transformable * _tranformable = nullptr;
   sf::Drawable *      _drawable     = nullptr;
};

} // ns gui
} // ns pukan

#endif // ELEMENT_HPP
