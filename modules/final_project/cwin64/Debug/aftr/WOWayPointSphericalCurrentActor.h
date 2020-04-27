#pragma once

#include "WOWayPointSpherical.h"
#include <string>
#include <vector>

namespace Aftr
{
/**
\author Chad Mourning

The WOWayPoint class is used for any event driven interaction.
There are 3 basic types of WayPoints:  
Standard WayPoints' "onTrigger" method is called when an activator passes within \see radius distance of it.
Inverse WayPoints' "onTrigger" method is called when an activator passes outside of the \see radius
Global WayPoints' "onTrigger method is called whenever all of its prerequisettes have been met and it is enabled.
All subtypes of way points can be one-use or multi-use.  Mutli-use way points are automatically reenabled based on a given frequency (defauly is 1 second).

*/
class WOWayPointSphericalCurrentActor : public WOWayPointSpherical
{
public:	
   static WOWayPointSphericalCurrentActor* New( const WayPointParametersBase& params, float radius );
   /**
   Destructor
   */
   virtual ~WOWayPointSphericalCurrentActor();
   virtual void onTrigger();
   virtual void onUpdateWO();
protected:
   /**
   Constructor
   */
   WOWayPointSphericalCurrentActor( const WayPointParametersBase& params, float radius );
};

}

