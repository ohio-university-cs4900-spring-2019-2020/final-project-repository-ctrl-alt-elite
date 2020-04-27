#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUISpeedStripNumLine : public WOGUI
{
public:
   static WOGUISpeedStripNumLine* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUISpeedStripNumLine();
   virtual void setSpeed( float speedFt );

   static const float MAX_RANGE; ///< Max range this speed strip accomodates

protected:
   WOGUISpeedStripNumLine( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );
   virtual void createSpeedLabels();
   virtual void updateSpeedLabels();
   virtual float getLabelPosition( unsigned int idx );

   float speed; ///< current speed the speed strip is displaying

   static const int NUM_LABELS = 9; ///< Number of labels to display on the speed strip
   static const float NUM_TEX_REPEATS; ///< Number of times tex is repeated
   static const float TICK_LEN;

   std::vector< WOGUILabel* > speedLbls; ///< 0th index is the top label (highest speed), last index is lowest label (lowest speed)
};

} //namespace Aftr

