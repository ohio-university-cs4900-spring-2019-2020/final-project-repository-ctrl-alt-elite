//----------------------------------------------------------------------------
//Description: The WOCarJeep class
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOVehicleFourWheeled.h"

//----------------------------------------------------------------------------
//Description: The WOCarJeep class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOCarJeep : public WOVehicleFourWheeled
{

public:
   static WOCarJeep* New( const std::string& modelFileName, const std::vector< std::string >& wheels );
   WOCarJeep();
   virtual ~WOCarJeep();

   //User Keyboard Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   //-----------------------------------

   ///1. Apply forces to the bodies as necessary.
   ///2. Adjust the joint parameters as necessary.
   virtual void ODEupdateForcesAndJoints();

   void setEngineSpeed( int inEngineSpeed ) { this->engineSpeed = inEngineSpeed; }
   int getEngineSpeed() { return this->engineSpeed; }

   ///Sets the direction the wheels turn
   ///-1: Turn Wheels Right
   /// 0: Turn Wheels Straight
   /// 1: Turn Wheels Left
   void setWheelDirection( int direction ) { this->wheelDirection = direction; }
   int getWheelDirection() { return this->wheelDirection; }
   

protected:
   virtual void onCreate( const std::string& chassisFileName, const std::vector< std::string >& wheelFileNames );
   ///Creates the graphical wheel models and positions them relative to the car body graphical model.
   //virtual void createWheels( const std::vector< std::string >& wheels );

   float paramShrinkBBoxInXAxisPercent;

};
} //namespace Aftr
#endif
