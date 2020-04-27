#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_NV_PHYSX

#include "WONVPhysX.h"

namespace Aftr
{

class WONVStaticPlane : public WONVPhysX
{
public:

   static WONVStaticPlane* New(const std::string& modelFileName, const Vector& scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstFLAT );
   virtual ~WONVStaticPlane();

   //Must implement the abstract virtual methods defined in IFaceWONVPhysX interface
   virtual void onCreateNVPhysXActor();
   virtual void updatePoseFromPhysicsEngine( const PxActiveTransform* trans );

protected:
   WONVStaticPlane();

};

} //namespace Aftr

#endif