//----------------------------------------------------------------------------
//Description: The WOVehicleFourWheeled class
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"
#include <vector>

//----------------------------------------------------------------------------
//Description: The WOVehicleFourWheeled class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOVehicleFourWheeled : public WOODE
{

public:
   static WOVehicleFourWheeled* New( const std::string& modelFileName, const std::vector< std::string >& wheels );

   virtual ~WOVehicleFourWheeled();

   virtual void initODESurface();

   //User Keyboard Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   //-----------------------------------

   ///Creates the ODE Prims of the car body and wheels and the joints between them.
   virtual void ODEinitializeInODE();

   /**
      Destroys all ODE objects representing the physics of this wheeled vehicle
   */
   virtual void ODEdestroyInODE();

   ///1. Apply forces to the bodies as necessary.
   ///2. Adjust the joint parameters as necessary.
   virtual void ODEupdateForcesAndJoints();

   //virtual void onPhysicsEngineTick();

   virtual void disableAutoUprightTimer();
   virtual void enableAutoUprightTimer();

   /// The vehicle checks to see if it is 'upright' periodically at the in passed interval (in milliseconds).
   virtual void setAutoUprightTimer( unsigned int milliSecondsBetweenUprightCheck );
   /// Returns the time, in milliseconds, of how often the vehicle checks to see if it is 'upright'.
   virtual unsigned int getAutoUprightTimer();

   void setEngineSpeed( int inEngineSpeed ) { this->engineSpeed = inEngineSpeed; }
   int getEngineSpeed() { return this->engineSpeed; }

   ///Sets the direction the wheels turn
   ///-1: Turn Wheels Right
   /// 0: Turn Wheels Straight
   /// 1: Turn Wheels Left
   void setWheelDirection( int direction ) { this->wheelDirection = direction; }
   int getWheelDirection() { return this->wheelDirection; }
   

protected:
   WOVehicleFourWheeled();
   virtual void onCreate( const std::string& chassisFileName, const std::vector< std::string >& wheelFileNames );

   ///Creates the graphical wheel models and positions them relative to the car body graphical model.
   virtual void createWheels( const std::vector< std::string >& wheels );
   virtual bool uprightCar();
   virtual Vector getWheelPositionOffset( unsigned int wheelPosition );
   virtual Vector computeWheelPositionOffsetFromCenter( float relRotAboutNormal, float relScalarDistFromCenter, float scalarDistBelowBody );

   std::vector< WOODE* > wheels;
   std::vector< dJointID > odeWheelJoints;

   int engineSpeed;
   int wheelDirection; //-1 = Left; 0 = Straight; 1 = Right
   bool pushingFrontBackArrow;      //used by OnKeyDown method
	bool pushingLeftRightArrow;      //used by OnKeyDown method

   float paramWheelSpeedScalar; ///max velocity
   float paramWheelTorque; ///max force (Newton-meters) to achieve max velocity
   float paramWheelChangeSteeringVel; ///how fast tires turn left to right and vice-versa

   float paramMaxWheelTurningAngle;

   float paramTireFLRelRadRotAboutNormal;
   float paramTireFLRelScalarDistFromCenter;
   
   float paramTireFRRelRadRotAboutNormal;
   float paramTireFRRelScalarDistFromCenter;

   float paramTireBLRelRadRotAboutNormal;
   float paramTireBLRelScalarDistFromCenter;

   float paramTireBRRelRadRotAboutNormal;
   float paramTireBRRelScalarDistFromCenter;

   float paramTireOffsetFromBody;
   float paramTireOffsetBelowBody;
   float paramTireMass;

   unsigned int uprightResetTimer;
   bool uprightResetTimerEnabled;

};
} //namespace Aftr
#endif
