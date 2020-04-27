#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOForce.h"


namespace Aftr
{

/**
   \class WOForceThrusterDepricated
   \author Scott Nykl
   This class represents Thrusters... Yell at Scott to document this thing...
   He's been really busy...

   /{
*/

class WOForceThruster : public WOForce
{

public:
   static WOForceThruster* New( WOODE* parent, float maxThrust, const Vector& relativeThrusterLocationFromParent = Vector(0,0,0) );

   /** Destructor */
   virtual ~WOForceThruster();

   void setThrustMaxPower( float maxThrust ) { this->maxThrust = maxThrust; }

   /**
      Percentage of max thrust to set thruster power to. If the value is less than -1.0f or larger than 1.0f
      the value is clamped at -1.0f and 1.0f, respectively.
   */
   void setThrustPower( float percentOfMaxThrust );

   void setThrustDirRelTheta( float dirRelTheta );
   void setThrustDirRelPhi( float dirRelPhi );

   void changeThrustDirRelTheta( float dirRelTheta );
   void changeThrustDirRelPhi( float dirRelPhi );

   void resetThrusterOrientation();

   float getThrust() { return this->thrustUsed; }
   

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
   WOForceThruster( WOODE* parent, float maxThrust, const Vector& relativeThrusterLocationFromParent = Vector(0,0,0) );

   Vector relativeThrusterLocationFromParent;

   float maxThrust;
   float thrustUsed;
   float thrustDirRelTheta;
   float thrustDirRelPhi;
};

/**
   \}
*/

} //namespace Aftr
#endif
