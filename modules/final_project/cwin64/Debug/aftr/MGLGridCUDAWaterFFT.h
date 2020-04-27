#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_CUDA

#include "MGLGrid.h"

#include "cufft.h"

namespace Aftr
{
   class MGLGridCUDAWaterFFT : public MGLGrid
   {
   public:
      MGLGridCUDAWaterFFT( WO* parent, std::vector< std::vector< VectorD > > grid,
         float x, float y,
         unsigned int tilesInX, unsigned int tilesInY,
         float shininess, float chopiness,
         VectorD deepColor, VectorD shallowColor, VectorD skyColor);
      virtual ~MGLGridCUDAWaterFFT();
      virtual void render( const Camera& cam );
      void init(  unsigned int fidelitySquarred );
      void cudaInit( unsigned int fidelitySquarred );
      virtual void update();
      virtual void defineVertices();
      //virtual void defineTextureCoords();
   protected:
      GLuint posVertexBuffer;
      GLuint heightVertexBuffer;
      GLuint slopeVertexBuffer;

      unsigned int tilesInX;
      unsigned int tilesInY;

      float x;
      float y;

      //CUDA stuff
      unsigned int fftInputW, fftInputH;
      unsigned int fftInputSize;

      float  *d_heightVB;
      float2 *d_slopeVB;
      float  *d_meshPosVBO;
      GLuint *d_indexBuffer;

      // FFT data
      cufftHandle fftPlan;
      float2 *d_h0;
      float2 *d_ht;
      float2 *h_h0;
      float2 *d_slope;

      // pointers to device object
      float  *g_hptr;
      float2 *g_sptr;

      // simulation parameters
       float g;		        // gravitational constant
       float A;	// wave scale factor
      float patchSize;        // patch size
      float windSpeed;
      float windDir;

      unsigned int timer;
      float animTime;
      float prevTime;
      float animationRate;

      float meshW;
      float meshH;

      void generate_h0();
      float phillips( float Kx, float Ky, float Vdir, float V, float A );
   };
}

#endif
