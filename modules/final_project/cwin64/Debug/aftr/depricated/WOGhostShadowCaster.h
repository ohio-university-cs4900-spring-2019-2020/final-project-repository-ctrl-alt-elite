#pragma once

#include "WO.h"
#include "IFaceShadowCaster.h"

namespace Steamie
{

   class WOGhostShadowCaster : public WO, public IFaceShadowCaster
   {
      public:
         static WOGhostShadowCaster* New(const std::string& str, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO);
         virtual ~WOGhostShadowCaster();
      protected:
         virtual void onCreate(const std::string& str, const Vector& scale, MESH_SHADING_TYPE shadingType);
         WOGhostShadowCaster();

   };
}

