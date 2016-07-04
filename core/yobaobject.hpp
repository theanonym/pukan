#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "pukan/common.hpp"
#include "pukan/math/math.hpp"

namespace pukan {

class YobaObject
{
public:
   typedef std::unique_ptr<YobaObject> ObjectPtr;
   typedef std::vector<std::unique_ptr<YobaObject> > ObjectsList;

public:
   YobaObject();
   YobaObject(YobaObject * parent);
   virtual ~YobaObject();

   virtual void onInit();
   virtual void onClean();
   virtual void onReset();
   virtual void onEvent(const sf::Event & event);
   virtual void onUpdate();
   virtual void onRender();

protected:
   virtual void onKeyPressed(const sf::Event::KeyEvent & event);
   virtual void onKeyReleased(const sf::Event::KeyEvent & event);
   virtual void onLeftMousePressed(const sf::Event::MouseButtonEvent & event);
   virtual void onLeftMouseReleased(const sf::Event::MouseButtonEvent & event);
   virtual void onRightMousePressed(const sf::Event::MouseButtonEvent & event);
   virtual void onRightMouseReleased(const sf::Event::MouseButtonEvent & event);
   virtual void onMiddleMousePressed(const sf::Event::MouseButtonEvent & event);
   virtual void onMiddleMouseReleased(const sf::Event::MouseButtonEvent & event);
   virtual void onMouseMoved(const sf::Event::MouseMoveEvent & event);
   virtual void onMouseWheelMoved(const sf::Event::MouseWheelEvent & event);

protected:
   void addChild(YobaObject * child);

   ObjectsList & getChilds();
   const ObjectsList & getChilds() const;\

   bool hasParent() const;
   YobaObject * getParent() const;

private:
   YobaObject * _parent = nullptr;
   ObjectsList  _childs;
};

}

#endif // OBJECT_HPP
