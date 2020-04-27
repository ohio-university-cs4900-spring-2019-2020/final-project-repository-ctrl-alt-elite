#pragma once

#include "WO.h"
#include <vector>

namespace Aftr
{

   class WOIntersectionIndicator;

class WOIntersectionIndicationRibbon : public WO
{
public:
   static WOIntersectionIndicationRibbon* New(WO* trackee, const std::vector<WOIntersectionIndicator*>& intersectorList, unsigned int intersectorThreshhold, unsigned int timeLimit, unsigned int timeGranularity);
   virtual ~WOIntersectionIndicationRibbon();
   virtual void onUpdateWO();
   virtual void start() { active = true; }
   virtual void stop() { active = false; }
   virtual void toggleActivity() { active = !active; }
   virtual void clear();
protected:
   WOIntersectionIndicationRibbon(WO* trackee, const std::vector<WOIntersectionIndicator*>& intersectorList, unsigned int intersectorThreshhold, unsigned int timeLimit, unsigned int timeGranularity);
   virtual void onCreate();
   //logic stuff
   unsigned int intersectorThreshhold;
   unsigned int timeLimit;
   unsigned int internalTimer;
   unsigned int timeGranularity;
   std::vector<WOIntersectionIndicator*> intersectorList;
   WO* trackee;
   unsigned int timeOffset;
   bool active;
};

}

