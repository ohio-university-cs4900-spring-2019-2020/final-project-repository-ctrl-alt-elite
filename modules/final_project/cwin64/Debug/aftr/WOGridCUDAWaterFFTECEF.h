#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_CUDA

#include "WOGridCUDAWaterFFT.h"

namespace Aftr
{

   class AftrFrameBufferObject;
   class WOGridECEFElevation;

   class WOGridCUDAWaterFFTECEF : public WOGridCUDAWaterFFT
   {
   public:
      static WOGridCUDAWaterFFTECEF* New( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int fidelityPerTile, unsigned int tilesInX, unsigned int tilesInY, const VectorD& scale = VectorD(1,1,1),
         float shininess = .5, float choppiness = 1.0,
         VectorD deepColor = VectorD(0, 0, .1f), VectorD shallowColor = VectorD(.1f,.4f,.3f), VectorD skyColor = VectorD(.5f, .5f, .5f), WOGridECEFElevation* target = NULL);
      virtual ~WOGridCUDAWaterFFTECEF();
   protected:
      WOGridCUDAWaterFFTECEF::WOGridCUDAWaterFFTECEF();
      virtual void onCreate( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int fidelityPerTile, unsigned int tilesInX, unsigned int tilesInY, const VectorD& scale,
         float shininess, float chopiness,
         VectorD deepColor, VectorD shallowColor, VectorD skyColor, WOGridECEFElevation* target);
   };

}

#endif
