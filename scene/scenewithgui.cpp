#include "pukan/scene/scenewithgui.hpp"
#include "pukan/gui/gui.hpp"

namespace pukan {

SceneWithGUI::SceneWithGUI(YobaObject * parent)
{
   _gui = new gui::GUI(parent);
}

SceneWithGUI::~SceneWithGUI()
{
}

gui::GUI * SceneWithGUI::getGUI()
{
   assert(_gui);
   return _gui;
}

const gui::GUI * SceneWithGUI::getGUI() const
{
   assert(_gui);
   return _gui;
}

}
