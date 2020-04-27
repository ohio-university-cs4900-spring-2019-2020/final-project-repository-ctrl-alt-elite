#pragma once

#include "AftrGlobals.h"
#include "Vector.h"

namespace Aftr
{

   enum class PHYSICS_ENGINE_TYPE : unsigned char { petNONE, petODE, petNVPHSYX };
   std::ostream& operator <<( std::ostream& out, const PHYSICS_ENGINE_TYPE& pet );

class IFace;

class PhysicsEngine
{
public:
   
   PhysicsEngine()
   {
      this->totalSimulationTimeElapsed = 0;
      this->timeStepIntervalInSeconds = 1.0f / 60.0f;
   }

   virtual ~PhysicsEngine();

   /**
      The input param must be a decendant of IFace; however, since, IFace
      inheritance is virtual, static_cast<>() and standard c-style casts
      cannot convert from a base class to a child class (the slower 
      dynamic_cast need be used). As a result the type of the input 
      variable is a void*; which can be static_cast<>() to the proper IFace.
      For example, two acceptable types for this void* are the IFaceWOODE and IFaceWONVPhysX.

      NOTE: It is important to explicitly cast the instance exactly as its IFace type as
      the input parameter, not anything else.
      For example, if the WONVPhysX::onCreateNVPhysXActor() invokes
      'this->NVPhysXEngine->onAddNewPhysicsActorToSimulation( (IFaceWONVPhysX*)this );'
      the explicit (IFaceWONVPhysX*) cast on 'this' is REQUIRED. Failure to do so will
      cause a pointer to 'this', which is a multiply virtual inherited object to be
      used instead. This multiply virtual inherited object is not able to be properly
      downcast using c-style (static) casting, as a result the internal member variables
      and methods are not properly set; this causes errors when the physics engine
      operates on the data.
   */
   virtual void onAddNewPhysicsActorToSimulation( void* IFaceType ) = 0;
   virtual bool updateWorld( float seconds ) { totalSimulationTimeElapsed += seconds; return true; }
   virtual bool updateWorld() { return this->updateWorld( this->timeStepIntervalInSeconds ); }
   virtual void syncGFXfromPhyx() = 0;
   virtual Vector getGravityNormalizedVector() = 0;
   virtual float getGravityScalar() = 0;
   virtual void setGravityScalar( float newGravityScalar ) = 0;
   virtual void setGravityNormalizedVector( const Vector& newGravityNormalizedVector ) = 0;
   virtual float getTotalSimulationTimeElapsed() { return totalSimulationTimeElapsed; }
   virtual float getTimeStepIntervalInSeconds() { return this->timeStepIntervalInSeconds; }
protected:

   virtual void onCreate() = 0;
   float totalSimulationTimeElapsed;
   float timeStepIntervalInSeconds;

};

} //namespace Aftr

