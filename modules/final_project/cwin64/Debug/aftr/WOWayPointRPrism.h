#pragma once

#include "WOWayPointAbstract.h"
#include <string>
#include <vector>

namespace Aftr
{

 
   /**

   Rectangular Prism Activation Volume Way Points - Note: Only works with axis aligned rectangular prisms

   */

class WOWayPointRPrism : public WOWayPointAbstract
{
public:	
   static WOWayPointRPrism* New( const WayPointParametersBase& params, Vector size );
   /**
   Destructor
   */
   virtual ~WOWayPointRPrism();
   virtual void onTrigger();
   Vector getSize(){return size;}
protected:
   /**
   Protected Constructor
   */
   WOWayPointRPrism( const WayPointParametersBase& params, Vector size );
   virtual void onCreate();
   Vector size;
   virtual bool activate(Aftr::WO* activator);

  
};

}

