#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOForce.h"
#include "WOBuoyancyFluid.h"

namespace Aftr
{

const static float BUOYANCY_MECHANICAL_EFFICIENCY = .9f;
const static float BUOYANCY_DRAG_COEF_XY = .5f;
const static float BUOYANCY_DRAG_COEF_Z  = .15f;

/**
   \class WOForceBuoy
   \author Scott Nykl
   This class represents Buoyant Forces... Yell at Scott to document this thing...
   He's been really busy...

   Look here; the implementation is based on this
   http://www.hypeskeptic.com/Mattias/DelphiODE/BuoyancyParticles.asp

   /{
*/

class WOForceBuoy : public WOForce
{

public:
   static WOForceBuoy* New( WOODE* parent, WOBuoyancyFluid* fluidBody, float radius );

   /** Destructor */
   virtual ~WOForceBuoy();
   

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
   virtual void ODEupdateForcesAndJoints();

protected:
   WOForceBuoy( WOODE* parent, WOBuoyancyFluid* fluidBody, float radius );

   /** Body of liquid this boat shall float in. */
   WOBuoyancyFluid* fluidBody;

   /** Radius of this WOForceBuoy */
   float radius;
   float diameter;
   float crossSectionalArea;
   float crossSectionalAreaDIV2;
   float volume;
   float forceTable[101]; // [0,100] waterHeight/Diameter ratio from 0 to 100 percent

   /**
      Stores the position that this WOForceBuoy was at during the
      last time and ODE TICK occurred. This is useful for computing
      the average velocity of the buoy over the last time step interval;
      this is necessary to compute DRAG forces accurately.

      This Vector gets initialized in this->ODEinitializeInODE()
      and gets updated as the VERY LAST step at each call to
      this->ODEupdateForcesAndJoints().
   */
   Vector prevPosition;


   /**
         height from liquid level to bottom of sphere
   */
   float height;

   void applyBuoyantForce();
   Vector* computeBuoyantForce();
   Vector* lookUpBuoyantForce();
   Vector* computeCenterOfBuoyancy();

   void applyDragForce();
   Vector* computeDragForce();

   void computeForceLookUpTable();
};

/**
   \}
*/

} //namespace Aftr
#endif
