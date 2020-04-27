#pragma once

#include "WO.h"
#include "IFaceShadowCaster.h"
#include <string>

namespace Steamie
{

   class WOShadowCaster : public WO, public IFaceShadowCaster
   {
   public:
      static WOShadowCaster* New(const std::string& str, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO);
      virtual ~WOShadowCaster(){};
   protected:
      virtual void onCreate(const std::string& str, const Vector& scale, MESH_SHADING_TYPE shadingType);
      WOShadowCaster();
   };

}

