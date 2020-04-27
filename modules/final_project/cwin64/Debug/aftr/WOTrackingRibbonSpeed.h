#pragma once

#include "WOTrackingRibbonBase.h"

namespace Aftr
{

   class WOTrackingRibbonSpeed: public WOTrackingRibbonBase
   {
   public:
      static WOTrackingRibbonSpeed* New(float speed, WO* trackee, const Vector& g);
      virtual ~WOTrackingRibbonSpeed();
      void onUpdateWO();
      void addTrackPoint(double time, const TrackInfo& p);
      float getRangeTime() { return static_cast<float>( timeEnd - timeBegin ); }
   protected:
      WOTrackingRibbonSpeed( float speed, WO* trackee, const Vector& g );
      float speed;//in virtual seconds-per-real second
      double timeBegin;
      double timeEnd;
   };

}

