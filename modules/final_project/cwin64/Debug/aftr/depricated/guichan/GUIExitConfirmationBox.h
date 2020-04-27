#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include "GUIBox.h"

namespace gcn
{
  class ImageFont;
  class Label;
  class Button;
}

namespace Steamie
{

class GUIExitConfirmationBoxButton;

class GUIExitConfirmationBox : public GUIBox
{
   friend class GUIExitConfirmationBoxButton;
public:
   GUIExitConfirmationBox(gcn::ImageFont* font, GLView* view, std::string text = "Are you sure you want to exit?");
   virtual ~GUIExitConfirmationBox();
protected:
   gcn::Label* label;
   GUIExitConfirmationBoxButton* butExit;
   GUIExitConfirmationBoxButton* dont;
};

}
#endif //STM_CONFIG_USE_GUICHAN
