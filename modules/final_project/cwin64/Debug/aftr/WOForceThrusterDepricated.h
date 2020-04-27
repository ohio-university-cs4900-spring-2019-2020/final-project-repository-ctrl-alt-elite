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

class WOForceThrusterDepricated : public WOForce
{

public:
   static WOForceThrusterDepricated* New( WOODE* parent, float maxThrust );

   /** Destructor */
   virtual ~WOForceThrusterDepricated();

   void setThrustMaxPower( float maxThrust ) { this->maxThrust = maxThrust; }
   void setThrustPower( float percentOfMaxThrust ) { this->thrustUsed = percentOfMaxThrust; }

   void setThrustDirRelTheta( float dirRelTheta ) { this->thrustDirRelTheta = dirRelTheta; this->usingRelAngles = true; }
   void setThrustDirRelPhi( float dirRelPhi ) { this->thrustDirRelPhi = dirRelPhi; this->usingRelAngles = true; }

   void setThrustDirAbsTheta( float dirAbsTheta ) { this->thrustDirAbsTheta = dirAbsTheta; this->usingRelAngles = false; }
   void setThrustDirAbsPhi( float dirAbsPhi ) { this->thrustDirAbsPhi = dirAbsPhi; this->usingRelAngles = false; }

   void changeThrustDirRelTheta( float deltaRelTheta ) { this->thrustDirRelTheta += deltaRelTheta; this->usingRelAngles = true; }
   void changeThrustDirRelPhi( float deltaRelPhi ) { this->thrustDirRelPhi += deltaRelPhi; this->usingRelAngles = true; }

   void changeThrustDirAbsTheta( float deltaAbsTheta ) { this->thrustDirAbsTheta += deltaAbsTheta; this->usingRelAngles = false; }
   void changeThrustDirAbsPhi( float deltaAbsPhi ) { this->thrustDirAbsPhi += deltaAbsPhi; this->usingRelAngles = false; }

   float getThrust() { return this->thrustUsed; }

   //Need to check if angles are absolute or relative - and might need to compute value before returning
   float getThrustDirRelTheta();
   float getThrustDirRelPhi();
   float getThrustAbsTheta();
   float getThrustAbsPhi();
   

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
   WOForceThrusterDepricated( WOODE* parent, float maxThrust );

   float maxThrust;
   float thrustUsed;
   float thrustDirRelTheta;
   float thrustDirRelPhi;
   float thrustDirAbsTheta;
   float thrustDirAbsPhi;
   bool usingRelAngles;


};

/**
   \}
*/

} //namespace Aftr
#endif
