#include "pukan/gui/guielement.hpp"

namespace pukan {
namespace gui {

Element::Element()
{
}

bool Element::isActive() const
{
   return _isActive;
}

void Element::setActive(bool active)
{
   _isActive = active;
}

bool Element::isMouseOver() const
{
   return _isMouseOver;
}

void Element::setMouseClickCallback(Element::MouseClickCallback callback)
{
   _hasMouseclickCallback = true;
   _mouseClickCallback = callback;
}

void Element::setMouseOverCallback(Element::MouseMoveCallback callback)
{
   _hasMouseMoveCallback = true;
   _mouseOverCallback = callback;
}

void Element::setMouseOutCallback(Element::MouseMoveCallback callback)
{
   _hasMouseMoveCallback = true;
   _mouseOutCallback = callback;
}

void Element::update()
{
   if(!isActive())
      return;
}

void Element::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
   if(!isActive())
      return;

   Vec2f originalPos = _tranformable->getPosition();
   _tranformable->setPosition(renderTarget.mapPixelToCoords(Vec2i(originalPos)));
   renderTarget.draw(*_drawable, renderStates);
   _tranformable->setPosition(originalPos);
}

Vec2f Element::getScreenPos() const
{
   return _tranformable->getPosition();
}

void Element::setScreenPos(const Vec2f & pos, bool center)
{
   if(!center)
   {
      _tranformable->setPosition(pos);
   }
   else
   {
      Recti bounds(getScreenBounds());
      _tranformable->setPosition(pos.x - bounds.w  / 2,
                                 pos.y - bounds.h / 2);
   }
}

bool Element::onMouseClick(const Vec2i & pos)
{
   if(!_hasMouseclickCallback)
      return false;

   bool isClicked = getScreenBounds().contains(pos);
   if(isClicked)
      _mouseClickCallback();

   return isClicked;
}

void Element::onMouseMove(const Vec2i & pos)
{
   if(!_hasMouseMoveCallback)
      return;

   bool isMouseOverNow = getScreenBounds().contains(pos);

   if(!isMouseOver() && !isMouseOverNow)
      return;

   if(!isMouseOver() && isMouseOverNow)
   {
      _isMouseOver = true;
      _mouseOverCallback();
   }

   if(isMouseOver() && !isMouseOverNow)
   {
      _isMouseOver = false;
      _mouseOutCallback();
   }
}

} // ns gui
} // ns pukan
