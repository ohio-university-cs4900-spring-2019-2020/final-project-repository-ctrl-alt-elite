#pragma once

#include "WO.h"

namespace Aftr
{

   class WOFresnelZones : public WO
   {
   public:
      static WOFresnelZones* New( unsigned int verticalResolution, unsigned int horizontalResolution, float length, float wavelength, unsigned int fresnelHarmonic);
      virtual ~WOFresnelZones();
   protected:
      WOFresnelZones();
      virtual void onCreate( unsigned int verticalResolution, unsigned int horizontalResolution, float length, float wavelength, unsigned int fresnelHarmonic);
   };

}

