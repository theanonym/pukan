#include "pukan/core/yobaobject.hpp"

namespace pukan {

YobaObject::YobaObject()
{
}

YobaObject::YobaObject(YobaObject * parent)
   : _parent(parent)
{
   parent->addChild(this);
}

YobaObject::~YobaObject()
{
//   if(hasParent())
//   {
//     YobaObject * parent = getParent();
//     ObjectsList & parentChilds = parent->getChilds();
//     auto removeIt = std::remove_if(parentChilds.begin(),
//                                    parentChilds.end(),
//                                    [this](const ObjectPtr & object)
//                                    { return object->get() == this; });
//     parentChilds.erase(parentChilds.begin(), removeIt);
//   }
}

void YobaObject::onInit()
{
   for(ObjectPtr & child : getChilds())
      child->onInit();
}

void YobaObject::onClean()
{
   for(ObjectPtr & child : getChilds())
      child->onClean();
}

void YobaObject::onReset()
{
}

void YobaObject::onEvent(const sf::Event & event)
{
   switch(event.type)
   {
      case sf::Event::KeyPressed:      onKeyPressed(event.key); break;
      case sf::Event::KeyReleased:     onKeyReleased(event.key); break;
      case sf::Event::MouseMoved:      onMouseMoved(event.mouseMove); break;
      case sf::Event::MouseWheelMoved: onMouseWheelMoved(event.mouseWheel); break;

      case sf::Event::MouseButtonPressed:
         switch(event.mouseButton.button)
         {
            case sf::Mouse::Left:   onLeftMousePressed(event.mouseButton); break;
            case sf::Mouse::Right:  onRightMousePressed(event.mouseButton); break;
            case sf::Mouse::Middle: onMiddleMousePressed(event.mouseButton); break;
            default: break;
         }
         break;

      case sf::Event::MouseButtonReleased:
         switch(event.mouseButton.button)
         {
            case sf::Mouse::Left:   onLeftMouseReleased(event.mouseButton); break;
            case sf::Mouse::Right:  onRightMouseReleased(event.mouseButton); break;
            case sf::Mouse::Middle: onMiddleMouseReleased(event.mouseButton); break;
            default: break;
         }
         break;

      default:
         break;
   }

   for(ObjectPtr & child : getChilds())
      child->onEvent(event);
}

void YobaObject::onUpdate()
{
   for(ObjectPtr & child : getChilds())
      child->onUpdate();
}

void YobaObject::onRender()
{
   for(ObjectPtr & child : getChilds())
      child->onRender();
}

void YobaObject::onKeyPressed(const sf::Event::KeyEvent &)
{
}

void YobaObject::onKeyReleased(const sf::Event::KeyEvent &)
{
}

void YobaObject::onLeftMousePressed(const sf::Event::MouseButtonEvent &)
{
}

void YobaObject::onLeftMouseReleased(const sf::Event::MouseButtonEvent &)
{
}

void YobaObject::onRightMousePressed(const sf::Event::MouseButtonEvent &)
{
}

void YobaObject::onRightMouseReleased(const sf::Event::MouseButtonEvent &)
{
}

void YobaObject::onMiddleMousePressed(const sf::Event::MouseButtonEvent &)
{
}

void YobaObject::onMiddleMouseReleased(const sf::Event::MouseButtonEvent &)
{
}

void YobaObject::onMouseMoved(const sf::Event::MouseMoveEvent &)
{
}

void YobaObject::onMouseWheelMoved(const sf::Event::MouseWheelEvent &)
{
}

void YobaObject::addChild(YobaObject * child)
{
   _childs.push_back(ObjectPtr(child));
}

YobaObject::ObjectsList & YobaObject::getChilds()
{
   return _childs;
}

const YobaObject::ObjectsList & YobaObject::getChilds() const
{
   return _childs;
}

bool YobaObject::hasParent() const
{
   return _parent != nullptr;
}

YobaObject * YobaObject::getParent() const
{
   return _parent;
}

}
