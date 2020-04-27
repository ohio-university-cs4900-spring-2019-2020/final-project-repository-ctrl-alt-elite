#pragma once

#include "WOWayPointAbstract.h"
#include <string>
#include <vector>

namespace Aftr
{
   /**
   \author Chad Mourning (modified by Scott Nykl)

   The WOWayPoint class is used for any event driven interaction.

   There are 3 basic types of WayPoints:  

   Standard WayPoints' "onTrigger" method is called when an activator passes within the disc formed by radius r around the origin with the given normal.

   All subtypes of way points can be one-use or multi-use.  Mutli-use way points are automatically reenabled based on a given frequency (defauly is 1 second).

   */
   class WOWayPointDisc : public WOWayPointAbstract
   {
   public:	
      static WOWayPointDisc* New(const WayPointParametersBase& params, float radius);
      /**
      Destructor
      */
      virtual ~WOWayPointDisc(){};
      /**
      Overload this method to do the behavior you want it to in inherited objects
      */
      virtual void onTrigger();
      virtual void onUpdateWO();
      float getRadius(){return radius;}
      virtual bool activate(WO* activator);
   protected:
       /**
       Protected Constructor
       */
       WOWayPointDisc( const WayPointParametersBase& params, float radius );
       virtual void onCreate();
       std::vector<Vector> oldPosition;
       float radius;
   };

}

