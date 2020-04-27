#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_CUDA

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL


#include "MGLGridCUDAWaterFFT.h"

namespace Aftr
{

   class WOGridECEFElevation;
   
   class MGLGridCUDAWaterFFTECEF : public MGLGridCUDAWaterFFT
   {
   public:
      static MGLGridCUDAWaterFFTECEF* New( WO* parentWO, std::vector< std::vector< VectorD > > grid, unsigned int tilesInX, unsigned int tilesInY, const VectorD& scale,
         float shininess, float chopiness,
         VectorD deepColor, VectorD shallowColor, VectorD skyColor, WOGridECEFElevation* target);
      virtual ~MGLGridCUDAWaterFFTECEF(  );
      virtual void render( const Camera& cam );
      virtual void defineVertices();
      virtual void update();

      void go() { isGoing = true; }
      void stop() { isGoing = false; }
   protected:
      virtual void onCreate();
      std::vector< VectorD > clonesCenterPoints;
      MGLGridCUDAWaterFFTECEF( WO* parentWO, std::vector< std::vector< VectorD > > grid, unsigned int tilesInX, unsigned int tilesInY, const VectorD& scale,
         float shininess, float chopiness,
         VectorD deepColor, VectorD shallowColor, VectorD skyColor, WOGridECEFElevation* target);
      int VBOcounter;

      void makePositionVBOs( unsigned index );

      std::vector< std::vector< std::vector< VectorD > > > gridOfGrids;
      std::vector< GLuint > positionHandles;
      //std::vector< GLuint > textureCoordHandles;

      bool isGoing;
      unsigned int internalTimer;
      unsigned int transitionTimer;

      WOGridECEFElevation* target;
      AftrFrameBufferObject* fbo;
   };

}

#endif
#endif

