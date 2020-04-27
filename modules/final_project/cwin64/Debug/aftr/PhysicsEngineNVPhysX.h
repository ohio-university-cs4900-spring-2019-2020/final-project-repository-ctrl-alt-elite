#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_NV_PHYSX

#include "PhysicsEngine.h"
#include "PxPhysicsAPI.h"
#include "PxDefaultCpuDispatcher.h"
#include "PxSimulationEventCallback.h"

using namespace physx;

//namespace physx
//{
//   class PxScene;
//   class PxPhysics;
//   class PxMaterial;
//   class PxDefaultCpuDispatcher;
//}


namespace Aftr
{

class IFaceWONVPhysX; //PxSimulationEventCallback //PxSimulationFilterCallback
                                                          
class PhysicsEngineNVPhysX : public PhysicsEngine, public PxSimulationEventCallback
{
public:
   static PhysicsEngineNVPhysX* New( float gravityScalar = -Aftr::GRAVITY, const Vector& gravityNormalizedVector = Vector(0,0,-1) );
   virtual ~PhysicsEngineNVPhysX();

   /**
      NOTE: It is important to explicitly cast the instance exactly as IFaceWONVPhysX* as
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
   virtual void onAddNewPhysicsActorToSimulation( void* IFaceWONVPhysXInstance );

   virtual bool updateWorld( float seconds );
   virtual void syncGFXfromPhyx();

   virtual Vector getGravityNormalizedVector();
   virtual float getGravityScalar();
   virtual void setGravityScalar( float newGravityScalar );
   virtual void setGravityNormalizedVector( const Vector& newGravityNormalizedVector );

   virtual void customizeScene( PxSceneDesc* desc ) {}

   virtual void setActorShaderFilter( PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask );

   PxScene* getScene();
   PxPhysics* getPhysicsSDK() { return this->gPhysicsSDK; }
   PxMaterial* getDefaultMaterial() { return this->defaultMaterial; }

protected:
   PhysicsEngineNVPhysX( float gravityScalar = -Aftr::GRAVITY, const Vector& gravityNormalizedVector = Vector(0,0,-1) );
   virtual void onCreate();
   virtual void createNVPhysXActors();

   PxPhysics* gPhysicsSDK;
   PxScene* gScene;
   PxMaterial* defaultMaterial;
   PxDefaultCpuDispatcher* cpuDispatcher;

   float gravityScalar;
   Vector gravityDir;



};


} //namespace Aftr

#endif //AFTR_CONFIG_USE_NV_PHYSX

