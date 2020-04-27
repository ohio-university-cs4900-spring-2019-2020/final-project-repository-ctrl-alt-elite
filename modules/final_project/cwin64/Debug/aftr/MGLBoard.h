#pragma once

#include "MGL.h"
#include <string>

namespace Aftr
{
   class WOBoard;
   class IndexedGeometryQuad;
   class IndexedGeometryRectangularPrism;

   class MGLBoard : public MGL
   {
   public:

      MGLBoard( WO* parentWO, std::string textures[3] = NULL,
         float length = 2,
         float width = 1,
         int slices = 3,					
         bool vert = false, ///alignment, true = vertical ; false = horizontal
         Vector color = Vector(0,0,0));
      ~MGLBoard();  
      virtual void render( const Camera& cam );
      void setRotateAngle(float x) { rotated = x; } 
   protected:
      WOBoard* parent;
      float length;
      float width;
      int slices;
      bool align;
      Vector color;
      unsigned int time;
      float speed;
      void drawSign();
      void drawSlice(int s, int i);
      float rotated;

      IndexedGeometryRectangularPrism* prism1and2;
      IndexedGeometryRectangularPrism* prism3;
      IndexedGeometryRectangularPrism* prism4;
   };


}  //namespace Aftr

