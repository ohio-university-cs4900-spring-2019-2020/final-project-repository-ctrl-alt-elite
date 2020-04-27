#pragma once

#include "WOWayPointDisc.h"

namespace Aftr
{

   class WOWayPointDiscCurrentActor : public WOWayPointDisc
   {
   public:
      static WOWayPointDiscCurrentActor* New(const WayPointParametersBase& params, float radius);
      virtual void onUpdateWO();
      virtual ~WOWayPointDiscCurrentActor(){}
   protected:
      WOWayPointDiscCurrentActor(const WayPointParametersBase& params, float radius);
   };

}

