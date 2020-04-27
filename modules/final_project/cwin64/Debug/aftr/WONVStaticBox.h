#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_NV_PHYSX

#include "WONVPhysX.h"

namespace Aftr
{

class WONVStaticBox : public WONVPhysX
{
public:

   static WONVStaticBox* New(const std::string& modelFileName, const Vector& scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstFLAT );
   virtual ~WONVStaticBox();

   //Must implement the abstract virtual methods defined in IFaceWONVPhysX interface
   virtual void onCreateNVPhysXActor();
   //virtual void updatePoseFromPhysicsEngine();

protected:
   WONVStaticBox();

};

}

#endif //AFTR_CONFIG_USE_NV_PHYSX
