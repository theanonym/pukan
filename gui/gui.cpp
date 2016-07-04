#include "pukan/gui/gui.hpp"
#include "pukan/gui/guielement.hpp"
#include "pukan/core/services/random.hpp"
#include "pukan/core/services/renderer.hpp"

namespace pukan {
namespace gui {

GUI::GUI(YobaObject * parent)
   : YobaObject(parent)
{
}

void GUI::onUpdate()
{
   for(auto it = _elements.begin(); it != _elements.end();)
      if(it->second->needToRemove())
         it = _elements.erase(it);
      else
         it++;
}

void GUI::onRender()
{
   //TODO disableCamera
   for(auto it = _elements.begin(); it != _elements.end(); it++)
      Renderer::get().draw(*it->second);
}

void GUI::onLeftMousePressed(const sf::Event::MouseButtonEvent & event)
{
   for(const auto & pair : _elements)
      if(pair.second->isActive())
         if(pair.second->onMouseClick(Vec2i(event.x, event.y)))
            break;
}

void GUI::onMouseMoved(const sf::Event::MouseMoveEvent & event)
{
   for(const auto & pair : _elements)
      if(pair.second->isActive())
         pair.second->onMouseMove(Vec2i(event.x, event.y));
}

void GUI::addElement(Element * element)
{
   addElement("random" + b::lexical_cast<std::string>(Random::get().getReal(0.f, 1.f)), element);
}

void GUI::addElement(const std::string & name, Element * element)
{
   auto it = std::find_if(_elements.begin(), _elements.end(),
                          [name](const Element::Pair & pair)
                          { return pair.first == name; });

   if(it != _elements.end())
      ythrow(Error, (b::format("Элемент с именем `%1%' уже существует.") % name).str());

   _elements.push_back(std::make_pair(name, Element::Ptr(element)));
}

Element * GUI::getElement(const std::string & name) const
{
   auto it = std::find_if(_elements.begin(), _elements.end(),
                          [name](const Element::Pair & pair)
                          { return pair.first == name; });

   if(it == _elements.end())
      ythrow(Error, (b::format("Элемент с именем `%1%' не найден.") % name).str());

   return it->second.get();
}

void GUI::removeTemporaryElements()
{
   for(Element::Pair &  pair : _elements)
      if(pair.second->hasTimeLimit())
         pair.second->removeAfter(0);
   /*
   for(auto it = _elements.begin(); it != _elements.end();)
      if(it->second->hasTimelimit())
         it = _elements.erase(it);
      else
         it++;
   */
}

} // ns gui
} // ns pukan
