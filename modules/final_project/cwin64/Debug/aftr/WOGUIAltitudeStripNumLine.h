#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIAltitudeStripNumLine : public WOGUI
{
public:
   static WOGUIAltitudeStripNumLine* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUIAltitudeStripNumLine();
   virtual void setAltitude( float altitudeFt );

   static const float MAX_RANGE; ///< Max range this altitude strip accomodates

protected:
   WOGUIAltitudeStripNumLine( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );
   virtual void createAltLabels();
   virtual void updateAltLabels();
   virtual float getLabelPosition( unsigned int idx );

   float alt; ///< current altitude the altitude strip is displaying

   static const int NUM_LABELS = 9; ///< Number of labels to display on the altitude strip
   static const float NUM_TEX_REPEATS; ///< Number of times tex is repeated
   static const float TICK_LEN; ///< Distance between each major tick mark on the number line (NUM_TEX_REPEATS/(NUMLABELS-1))

   std::vector< WOGUILabel* > altLbls; ///< 0th index is the top label (highest altitude), last index is lowest label (lowest altitude)
};

} //namespace Aftr

