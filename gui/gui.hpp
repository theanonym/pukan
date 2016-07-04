#ifndef GUI_HPP
#define GUI_HPP

#include "pukan/common.hpp"
#include "pukan/core/yobaobject.hpp"
#include "pukan/gui/guierror.hpp"

namespace pukan {
namespace gui {

class Element;

class GUI : public YobaObject
{
public:
   GUI(YobaObject * parent);

   void onUpdate();
   void onRender();

   void onLeftMousePressed(const sf::Event::MouseButtonEvent & event);
   void onMouseMoved(const sf::Event::MouseMoveEvent & event);

   void addElement(Element * element);
   void addElement(const std::string & name, Element * element);
   Element * getElement(const std::string & name) const;
   template<typename T>
   T * getElement(const std::string & name) const
   {
      return static_cast<T *>(getElement(name));
   }

   void removeTemporaryElements();

private:
   std::vector<std::pair<std::string, std::unique_ptr<Element> > > _elements;
};

} // ns gui
} // ns pukan

#endif // GUI_HPP
