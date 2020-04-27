#pragma once

#include "WOWayPointDisc.h"
#include <string>
#include <vector>

namespace Aftr
{
   /**
   \author Chad Mourning (modified by Scott Nykl)
   */
   class WOWayPointDiscSingleActor : public WOWayPointDisc
   {
   public:	
      static WOWayPointDiscSingleActor* New(const WayPointParametersBase& params, float radius);
      /**
      Destructor
      */
      virtual ~WOWayPointDiscSingleActor(){};
      /**
      Overload this method to do the behavior you want it to in inherited objects
      */
      virtual void onTrigger();
      virtual void onUpdateWO();
   protected:
      /**
      Protected Constructor
      */
      WOWayPointDiscSingleActor( const WayPointParametersBase& params, float radius );
   };
}

