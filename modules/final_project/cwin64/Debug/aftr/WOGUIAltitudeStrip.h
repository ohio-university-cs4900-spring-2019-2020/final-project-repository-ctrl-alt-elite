#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIAltitudeStripNumLine;
class WOGUIAltitudeStripAltitudeText;
class WOGUIAltitudeStripWakeStrip;

class WOGUIAltitudeStrip : public WOGUI
{
public:
   static WOGUIAltitudeStrip* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUIAltitudeStrip();
   virtual void setAltitude( float altitudeFt );
   virtual void setWakeAltitude( float altitudeFt );
   float getCurrentAltitude();
   float getCurrentWakeAltitude();

protected:
   WOGUIAltitudeStrip( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   float alt; ///< current altitude the altitude strip is displaying
   float wakeAlt; ///< current altitude at which turbulence begins
   WOGUIAltitudeStripNumLine* numLine; ///< WO displaying the moving number line and texture
   WOGUIAltitudeStripAltitudeText* altBox; ///< WO displaying the current altitude
   WOGUIAltitudeStripWakeStrip* wakeStrip; ///< WO displaying the turbulence
   WOGUI* centerLine; ///< Centered arrow pointing at the current altitude
};

} //namespace Aftr

