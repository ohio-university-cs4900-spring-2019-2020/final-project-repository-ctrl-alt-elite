#pragma once

#include "WOOperatorItinerary.h"

namespace Aftr
{

   class WOOperatorItineraryLoop : public WOOperatorItinerary
   {
   public:
      static WOOperatorItineraryLoop* New(WO* itineraree, AftrItinerary* itinerary);
   protected:
      WOOperatorItineraryLoop(WO* itineraree, AftrItinerary* itinerary);
      virtual ~WOOperatorItineraryLoop(){}
      virtual void onUpdateWO();
   };

}

