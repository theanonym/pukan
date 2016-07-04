#ifndef SCENEWITHGUI_HPP
#define SCENEWITHGUI_HPP

#include "pukan/common.hpp"

namespace pukan {

class YobaObject;
namespace gui { class GUI; }

class SceneWithGUI
{
public:
   SceneWithGUI(YobaObject * parent);
   virtual ~SceneWithGUI();

protected:
   gui::GUI * getGUI();
   const gui::GUI * getGUI() const;

private:
   gui::GUI * _gui;
};

}

#endif // SCENEWITHGUI_HPP
