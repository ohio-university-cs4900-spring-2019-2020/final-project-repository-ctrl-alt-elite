//#pragma once
//
//#include "AftrConfig.h"
//#ifdef AFTR_CONFIG_USE_NV_PHYSX
//
//#include "WONVPhysX.h"
//
//namespace Aftr
//{
//
//class WONVFluidDrain : public WONVPhysX
//{
//public:
//
//   static WONVFluidDrain* New(const std::string& modelFileName, const Vector& scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstFLAT );
//   virtual ~WONVFluidDrain();
//
//   //Must implement the abstract virtual methods defined in IFaceWONVPhysX interface
//   virtual void onCreateNVPhysXActor();
//   //virtual void updatePoseFromPhysicsEngine();
//   bool isDraining();
//   void isDraining( bool beginDraining );
//
//protected:
//   WONVFluidDrain();
//
//};
//
//}
//
//#endif //AFTR_CONFIG_USE_NV_PHYSX
//