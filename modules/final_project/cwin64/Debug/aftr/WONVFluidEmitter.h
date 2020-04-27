//#pragma once
//#include "AftrConfig.h"
//#ifdef AFTR_CONFIG_USE_NV_PHYSX
//
//#include "PxPhysicsAPI.h"
//#include "WONVFluid.h"
//
//namespace Aftr
//{
//
//class WONVFluidEmitter : public WONVFluid
//{
//public:
//   static WONVFluidEmitter* New( WONVPhysX* emitterBase, const Vector& emissionPtRelToBaseCenter, unsigned int numParticles );
//   virtual ~WONVFluidEmitter();
//
//   virtual void onCreateNVPhysXActor();
//   //virtual void updatePoseFromPhysicsEngine();
//   bool isEmitting();
//   void toggleIsEmitting();
//   void startEmitting();
//   void stopEmitting();
//
//protected:
//   virtual void onCreate();
//   WONVFluidEmitter( WONVPhysX* emitterBase, const Vector& emissionPtRelToBaseCenter, unsigned int numParticles );
//
//   //virtual void createInitialFluidState( NxFluidDesc_Template<>& desc );
//   virtual void createFluid( NxFluidDesc_Template<>& desc );
//
//   //this->model is the fluid emitted from the emitter
//   WONVPhysX* emitterBase; ///< Child which graphically represents the emitter
//   Vector emissionPtRelToBaseCenter; ///< Point from which particles are emitted. emitterBase.position + (emitter.orietation * emissionPtRelToBaseCenter)
//   NxFluidEmitter* fluidEmitter; ///< Pointer to the PhysX fluid emitter for this object
//
//};
//
//} //namespace Aftr
//
//#endif //AFTR_CONFIG_USE_NV_PHYSX
//