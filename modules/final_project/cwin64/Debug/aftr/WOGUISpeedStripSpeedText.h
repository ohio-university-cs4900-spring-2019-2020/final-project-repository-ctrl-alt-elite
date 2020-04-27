#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUISpeedStripSpeedTextNumLine;

class WOGUISpeedStripSpeedText : public WOGUI
{
public:
   static WOGUISpeedStripSpeedText* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUISpeedStripSpeedText();
   virtual void setSpeed( float speedFt );

protected:
   WOGUISpeedStripSpeedText( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   float speed; ///< current speed the speed strip is displaying
};

} //namespace Aftr

