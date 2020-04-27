#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"

namespace Aftr
{

/** This class represents body parts of the human world object. This can be expanded to encompass any body part for animals, aliens,
    whatever. 
    */
class WOBodyPart : public WOODE
{

public:
   static WOBodyPart* New( WO* parent, const std::string& bodyPartFileName );
   
   virtual ~WOBodyPart();

   virtual void onMouseDownSelection( const SDL_MouseButtonEvent& e );


    /**
      Updates this object's force and/or joint information of the ODE Body JUST BEFORE an ODE step is taken. 
      For example, if this is a car, the torque force from the engines and joints attaching the wheels to the car body are updated here.
      If the object is made up of more than one ODE Prim, the associated joints linking the Prims together are updated in this method.
      This method will be used ONLY by ODE. Do not manually call this, otherwise ODE's state machine will become "undefined".
      All one needs to do here is:
      1. Apply forces to the bodies as necessary.
      2. Adjust the joint parameters as necessary.
   */
   virtual void ODEinitializeInODE() {}
   virtual void ODEdestroyInODE() {}
   virtual void ODEupdateForcesAndJoints() {}
   virtual void ODEupdateToNewPositionOrientation();


protected:
   WOBodyPart(WO* parent);
   
};

} //namespace Aftr

#endif
