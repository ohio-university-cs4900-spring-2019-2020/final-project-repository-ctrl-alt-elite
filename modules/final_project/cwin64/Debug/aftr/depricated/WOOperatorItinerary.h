#pragma once

#include "WO.h"

namespace Aftr
{
   class AftrItinerary;

   class WOOperatorItinerary : public WO
   {
   public:
      /**
         This retains ownership of the itinerary, but not the itineraree.
      */
      static WOOperatorItinerary* New(WO* itineraree, AftrItinerary* itinerary);
      virtual ~WOOperatorItinerary();
      virtual void onUpdateWO();
      void begin() { go = true; }
      void pause() { go = false; }
      void toggle() { go = !go; }
      void reset() { internalTimer = 0; }
      void backward() { goForward = false; }
      void forward() { goForward = true; }
      void toggleDirection() { goForward = !goForward; }
      unsigned int timeMultiplier;
   protected:
      virtual void onCreate();
      WOOperatorItinerary(WO* itineraree, AftrItinerary* itinerary);
      WO* itineraree;
      AftrItinerary* itinerary;
      unsigned int internalTimer;
      bool goForward;
      bool go;
   };
}

