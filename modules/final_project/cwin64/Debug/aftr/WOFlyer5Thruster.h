//----------------------------------------------------------------------------
//Description: The  class
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"


//----------------------------------------------------------------------------
//Description: The WOVehicleFourWheeled class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOForceThruster;

class WOFlyer5Thruster : public WOODE
{
public:
   static WOFlyer5Thruster* New( const std::string& modelFileName, Vector scale = Vector(1,1,1) );
   virtual ~WOFlyer5Thruster();

   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   /**
      overloaded updateforcesandjoints
   */
   virtual void ODEupdateForcesAndJoints();

   virtual void onUpdateWO();

   WOForceThruster* getThrustCenter();
   WOForceThruster* getThrustFront();
   WOForceThruster* getThrustRear();
   WOForceThruster* getThrustLeft();
   WOForceThruster* getThrustRight();

protected:

   WOFlyer5Thruster();
   virtual void onCreate( const std::string& modelFileName, const Vector& scale );

   //#ifdef AFTR_CONFIG_USE_IPHONE
   virtual void updateViaIPhoneAccelerometer();
   float iPhoneAngularDampingScale;
   bool updateIPhoneAngularDampingScale;
   //#endif

   WOForceThruster* thrustCenter;
   WOForceThruster* thrustFront;
   WOForceThruster* thrustRear;
   WOForceThruster* thrustLeft;
   WOForceThruster* thrustRight;

   virtual void createThrusters();
   virtual void toggleThrusterVisibility();
   bool pushingFrontBackArrow;      ///used by onKeyDown/onKeyUp method
	bool pushingLeftRightArrow;      ///used by onKeyDown/onKeyUp method
};
} //namespace Aftr
#endif
