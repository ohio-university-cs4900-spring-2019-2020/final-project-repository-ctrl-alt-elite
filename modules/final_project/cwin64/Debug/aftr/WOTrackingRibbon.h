#pragma once

#include "WOTrackingRibbonBase.h"

namespace Aftr
{
class TrackInfo;

class WOTrackingRibbon : public WOTrackingRibbonBase
{
public:
   ///constructor
   static WOTrackingRibbon* New(unsigned int animationTimer, WO* trackee = nullptr, Vector g = Vector(0,0,1));
   ///destructor
   virtual ~WOTrackingRibbon();
     
   ///update
   void onUpdateWO();

   virtual void start();
   virtual void reset();
   void clear();

      
   /*
   Mutators and Accessors (when applicable)
   */
   ///set total time ribbon takes to complete
   ///if used while in progress, current ribbon will maintain completion %
   void setAnimationTimer(unsigned int x);

   void setTimeOffset(double x) { timeOffset = x; }
   double getTimeOffset() { return timeOffset; }
   void setInternalTimerPercentage( float percent ) { internalTimer = static_cast<unsigned int>( animationTimer * percent ); }
      
protected:
   WOTrackingRibbon(unsigned int animationTimer, WO* trackee, Vector g);
    
   //timer stuff
   unsigned int internalTimer;
   unsigned int animationTimer;
   unsigned int previousTime;
      
   double timeOffset;
};

}

