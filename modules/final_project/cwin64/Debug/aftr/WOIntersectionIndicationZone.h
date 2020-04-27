#pragma once

#include "WO.h"
#include "Camera.h"
#include <vector>

namespace Aftr
{

   class WOIntersectionIndicationZone : public WO
   {
   public:
      static WOIntersectionIndicationZone* New( float length, float width, std::vector< WO* > occluders );
      virtual ~WOIntersectionIndicationZone();
      void increaseResolution();
     
   protected:
      void onCreate(float length, float width, std::vector< WO* > occluders);
      WOIntersectionIndicationZone();
   };

}