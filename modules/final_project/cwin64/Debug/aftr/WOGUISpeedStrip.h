#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUISpeedStripNumLine;
class WOGUISpeedStripSpeedText;
class WOGUISpeedStripWakeStrip;

class WOGUISpeedStrip : public WOGUI
{
public:
   static WOGUISpeedStrip* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUISpeedStrip();
   virtual void setSpeed( float speedKnots );
   float getCurrentSpeed();

protected:
   WOGUISpeedStrip( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   float speed; ///< current speed the speed strip is displaying
   WOGUISpeedStripNumLine* numLine; ///< WO displaying the moving number line and texture
   WOGUISpeedStripSpeedText* speedBox; ///< WO displaying the current speed
   WOGUI* centerLine; ///< Centered arrow pointing at the current speed
};

} //namespace Aftr

