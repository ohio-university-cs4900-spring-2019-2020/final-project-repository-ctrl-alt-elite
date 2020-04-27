#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIAltitudeStripWakeStrip : public WOGUI
{
public:
   static WOGUIAltitudeStripWakeStrip* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUIAltitudeStripWakeStrip();
   virtual void setWakeAltitude( float altitudeFt );

protected:
   WOGUIAltitudeStripWakeStrip( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );
   virtual void updateWakeStrip();

   float wakeAlt; ///< current altitude the altitude strip is displaying
};

} //namespace Aftr

