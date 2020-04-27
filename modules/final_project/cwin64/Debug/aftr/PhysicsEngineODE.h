//----------------------------------------------------------------------------
//Description: The Physics Engine class
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include "PhysicsEngine.h"
#include "Vector.h"
#include "AftrGlobals.h"

namespace Aftr
{
class WOODE;
class IFaceWOODE;

class PhysicsEngineODE : public PhysicsEngine
{
public:
   static PhysicsEngineODE* New( float gravityScalar = -Aftr::GRAVITY, const Vector& gravityNormalizedVector = Vector(0,0,-1) );

   virtual ~PhysicsEngineODE();

   /**
      NOTE: It is important to explicitly cast the instance exactly as IFaceWOODE* as
      the input parameter, not anything else.
      For example, if the WOODE::ODEinitializeInODE() invokes
      'ODEPhysicsEngine->onAddNewPhysicsActorToSimulation( (IFaceWOODE*)this );'
      the explicit (IFaceWOODE*) cast on 'this' is REQUIRED. Failure to do so will
      cause a pointer to 'this', which is a multiply virtual inherited object to be
      used instead. This multiply virtual inherited object is not able to be properly
      downcast using c-style (static) casting, as a result the internal member variables
      and methods are not properly set; this causes errors when the physics engine
      operates on the data.
   */
   virtual void onAddNewPhysicsActorToSimulation( void* IFaceWOODEInstance );
   virtual bool updateWorld( float seconds );
   virtual void syncGFXfromPhyx();
   
   virtual float getGravityScalar(){ return gravityScalar; }
   virtual Vector getGravityNormalizedVector(){ return gravityNormalizedVector; }
   virtual void setGravityScalar( float newGravityScalar );
   virtual void setGravityNormalizedVector( const Vector& newGravityNormalizedVector );
   
   bool getUsingODEQuickStep() { return this->useODEQuickStep; }
   void setUsingODEQuickStep( bool useQuickStep ) { this->useODEQuickStep = useQuickStep; }
protected:
   
   PhysicsEngineODE( float gravityScalar = -Aftr::GRAVITY, const Vector& gravityNormalizedVector = Vector(0,0,-1) );
   virtual void onCreate();

   void setAutoDisableParameters( WOODE* wo );
   float gravityScalar;
   bool useODEQuickStep;
   Vector gravityNormalizedVector;
   std::vector< WO* >* worldLst;
};

} //namespace Aftr
