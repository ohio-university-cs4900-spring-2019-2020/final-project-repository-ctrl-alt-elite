#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIAltitudeStripAltitudeTextNumLine;

class WOGUIAltitudeStripAltitudeText : public WOGUI
{
public:
   static WOGUIAltitudeStripAltitudeText* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUIAltitudeStripAltitudeText();
   virtual void setAltitude( float altitudeFt );

protected:
   WOGUIAltitudeStripAltitudeText( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   float alt; ///< current altitude the altitude strip is displaying
};

} //namespace Aftr

