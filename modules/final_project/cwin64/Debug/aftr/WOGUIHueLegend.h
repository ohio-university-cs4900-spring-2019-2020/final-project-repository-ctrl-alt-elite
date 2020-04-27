#pragma once

#include "WO.h"

namespace Aftr
{

   class WOGUIHueLegend : public WO
   {
   public:
      static WOGUIHueLegend* New( float height, float width, size_t resolution, float minHue, float maxHue );
      virtual ~WOGUIHueLegend();
   protected:
      WOGUIHueLegend();
      virtual void onCreate( float height, float width, size_t resolution, float minHue, float maxHue );
   };

}

