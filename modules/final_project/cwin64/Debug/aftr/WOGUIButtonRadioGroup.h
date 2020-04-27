#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIButtonRadio;

class WOGUIButtonRadioGroup : public WOGUI
{
public:
   static WOGUIButtonRadioGroup* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUIButtonRadioGroup();

   WOGUIButtonRadio* getSelectedButtonRadio();

   virtual void onButtonRadioClicked( WOGUIButtonRadio* clickedButRdo );

protected:
   WOGUIButtonRadioGroup( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   /**
      Points to currently selected radio button contained in this radio button group.
      NULL is returned if no radio buttons are selected.
   */
   WOGUIButtonRadio* selectedButRdo;

};

} //namespace Aftr

