#pragma once

#include "WOWayPointDisc.h"
#include <string>
#include <vector>

namespace Aftr
{
   /**
   \author Chad Mourning (modified by Scott Nykl)
   */
   class WOWayPointDiscStatic : public WOWayPointDisc
   {
   public:	
      static WOWayPointDiscStatic* New( const WayPointParametersBase& params, float radius );
      /**
      Destructor
      */
      virtual ~WOWayPointDiscStatic();
      /**
      Overload this method to do the behavior you want it to in inherited objects
      */
      virtual void onTrigger();
      virtual void onUpdateWO();
      void setNormal(Vector normal){this->normal = normal;}
   protected:
      /**
      Protected Constructor
      */
      WOWayPointDiscStatic( const WayPointParametersBase& params, float radius );
      Vector normal;
   };

}

