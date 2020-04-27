#pragma once

#include "MGL.h"

namespace Aftr
{

   class IndexedGeometrySphere;

   class MGLRadarSignalPropagation : public MGL
   {
   public:
      MGLRadarSignalPropagation( WO* parentWO );
      virtual ~MGLRadarSignalPropagation();
      virtual void render( const Camera& cam );

      void toggleRenderMode(); 
      void incNumSlices(); 
      void incNumStacks();
      void decNumSlices(); 
      void decNumStacks(); 
   protected:
      unsigned int renderMode;
      unsigned int numSlices;
      unsigned int numStacks;
      IndexedGeometrySphere* sphere;
   };
}

