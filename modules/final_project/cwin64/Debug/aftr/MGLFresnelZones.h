#pragma once

#include "MGL.h"

namespace Aftr
{

   class MGLFresnelZones : public MGL
   {
   public:
      static MGLFresnelZones* New( WO* parent, unsigned int verticalResolution, unsigned int horizontalResolution, float length, float wavelength, unsigned int fresnelHarmonic );
      virtual ~MGLFresnelZones();
      void render( const Camera& cam );
   protected:
      MGLFresnelZones( WO* parent );
      virtual void onCreate( unsigned int verticalResolution, unsigned int horizontalResolution, float length, float wavelength, unsigned int fresnelHarmonic );

      unsigned int verticalResolution;
      unsigned int horizontalResolution;
      float length;
      unsigned int fresnelHarmonic;
      float wavelength;

   };

}

