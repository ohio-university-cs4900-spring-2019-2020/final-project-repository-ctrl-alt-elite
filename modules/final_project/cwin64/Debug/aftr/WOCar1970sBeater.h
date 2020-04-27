//----------------------------------------------------------------------------
//Description: The WOCar1970sBeater class
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOVehicleFourWheeled.h"

//----------------------------------------------------------------------------
//Description: The WOCar1970sBeater class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOCar1970sBeater : public virtual WOVehicleFourWheeled
{

public:
   static WOCar1970sBeater* New( const std::string modelFileName, const std::vector< std::string >& wheels );
   virtual ~WOCar1970sBeater();

   //User Keyboard Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   //-----------------------------------

   ///1. Apply forces to the bodies as necessary.
   ///2. Adjust the joint parameters as necessary.
   virtual void ODEupdateForcesAndJoints();
   

protected:
   WOCar1970sBeater();

};
} //namespace Aftr
#endif
