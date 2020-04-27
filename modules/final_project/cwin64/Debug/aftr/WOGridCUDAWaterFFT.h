#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_CUDA


#include "WOGrid.h"

namespace Aftr
{
   class WOGridCUDAWaterFFT : public WOGrid
   {
   public:
      /**
      @param length Length in x
      @param width Width in y
      @param fidelitySquarred Fidelity of the grid in each direction (powers of 2, please)
      */
      static WOGridCUDAWaterFFT* New( float length, float width, unsigned int fidelitySquarred = 256, 
         unsigned int tilesInX = 1, unsigned tilesInY = 1,
         float shininess = .5, float choppiness = 1.0,
         VectorD deepColor = VectorD(0, 0, .1f), VectorD shallowColor = VectorD(.1f,.4f,.3f), VectorD skyColor = VectorD(.5f, .5f, .5f) );
      virtual void onUpdateWO();
   protected:
      virtual void onCreate( float length, float width, unsigned int fidelitySquarred = 256, 
         unsigned int tilesInX = 1, unsigned tilesInY = 1,
         float shininess = .5, float choppiness = 1.0,
         VectorD deepColor = VectorD(0, 0, .1f), VectorD shallowColor = VectorD(.1,.4,.3f), VectorD skyColor = VectorD(.5f, .5f, .5f));
      WOGridCUDAWaterFFT::WOGridCUDAWaterFFT();
      virtual ~WOGridCUDAWaterFFT();
   };
}

#endif
