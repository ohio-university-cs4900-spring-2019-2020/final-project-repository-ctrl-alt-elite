#pragma once
#include "MGL.h"

namespace Aftr
{
   class IndexedGeometryQuad;

   class MGLSevenSegmentDisplayOverlay : public MGL
   {
   public:
      MGLSevenSegmentDisplayOverlay( WO* parentWO, float height, float width);
      virtual ~MGLSevenSegmentDisplayOverlay();
      void increment();
      void decrement();
      void setValue(unsigned int x);
      virtual void render( const Camera& cam );
   protected:
      float height;
      float width;
      unsigned int value;
      void renderTop();
      void renderUpperLeft();
      void renderLowerLeft();
      void renderUpperRight();
      void renderLowerRight();
      void renderBottom();
      void renderCenter();
      IndexedGeometryQuad* quad;
   };

}

