#pragma once

#include "WOGUILabeledImage.h"

namespace Aftr
{

class WOGUIButton;

class WOGUIButtonRadio : public WOGUILabeledImage
{
public:

   static WOGUIButtonRadio* New( WOGUI* parentWO, const std::string& label );
   virtual ~WOGUIButtonRadio();

   virtual void onMouseClicked( const SDL_MouseButtonEvent& e );

   /**
      
   */
   virtual void isSelected( bool isSelected );
   virtual bool isSelected();

protected:
   WOGUIButtonRadio( WOGUI* parentWOGUI );
   virtual void onCreate( const std::string& label );

   enum RADIO_BUTTON_TEX_STATE { rbtsNOT_SELECTED = 0, rbtsSELECTED };

   bool IsSelected;
};

} //namespace Aftr

