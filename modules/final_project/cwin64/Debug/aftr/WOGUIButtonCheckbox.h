#pragma once

#include "WOGUILabeledImage.h"

namespace Aftr
{

class WOGUIButton;

class WOGUIButtonCheckbox : public WOGUILabeledImage
{
public:

   static WOGUIButtonCheckbox* New( WOGUI* parentWO, const std::string& label );
   virtual ~WOGUIButtonCheckbox();

   virtual void onMouseClicked( const SDL_MouseButtonEvent& e );

   /**
      
   */
   virtual void isSelected( bool isSelected );
   virtual bool isSelected();

protected:
   WOGUIButtonCheckbox( WOGUI* parentWOGUI );
   virtual void onCreate( const std::string& label );

   enum CHECKBOX_BUTTON_TEX_STATE { cbtsNOT_SELECTED = 0, cbtsSELECTED, cbtsOVERRIDDEN, cbtsNUM_TEX_STATES };

   bool IsSelected;
};

} //namespace Aftr

