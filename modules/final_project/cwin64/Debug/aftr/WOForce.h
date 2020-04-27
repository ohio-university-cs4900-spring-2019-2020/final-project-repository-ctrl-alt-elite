#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"
#include <string>


namespace Aftr
{

/**
   \class WOForce
   \author Scott Nykl
   This class represents any Forces... Yell at Scott to document this thing...
   He's been really busy...

   THIS CLASS IS PURELY ABSTRACT...

   /{
*/

class WOForce : public WOODE
{

public: 

   ///Abstract Class... No WOForce::New(), create decendant
   virtual void onCreate( float radius );
   virtual void onCreate( const std::string& modelFileName );
   /** Destructor */
   virtual ~WOForce();
   

   //ODE Specific
   //-----------------------------------
   //Methods specific for integrating this WO with ODE
   //Children of this class need to overload these methods so ODE can use these WorldObjects appropriately

   /**
      Creates the ODE representation of this WO. For example, if the WO is a Sphere, then the corresponding
      ODE geom, body, and mass objects associated with that Sphere are created inside this method. This method will be used ONLY by ODE.
      Do not manually call this, otherwise ODE's state machine will become "undefined".
   */
   virtual void ODEinitializeInODE();

   /**
      Updates this object's force and/or joint information of the ODE Body JUST BEFORE an ODE step is taken. 
      For example, if this is a car, the torque force from the engines and joints attaching the wheels to the car body are updated here.
      If the object is made up of more than one ODE Prim, the associated joints linking the Prims together are updated in this method.
      This method will be used ONLY by ODE. Do not manually call this, otherwise ODE's state machine will become "undefined".
      All one needs to do here is:
      1. Apply forces to the bodies as necessary.
      2. Adjust the joint parameters as necessary.
   */
   virtual void ODEupdateForcesAndJoints() = 0;

protected:
   WOForce(); //Abstract Class... No WOForce::New(), create decendant

};

/**
   \}
*/

} //namespace Aftr
#endif
