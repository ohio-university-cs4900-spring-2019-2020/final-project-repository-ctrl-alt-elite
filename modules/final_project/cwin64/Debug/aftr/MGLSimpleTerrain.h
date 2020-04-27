#pragma once

#include "MGL.h"
#include <string>

namespace Aftr
{

   class IndexedGeometryQuad;

   class MGLSimpleTerrain : public MGL
   {
   public:
      MGLSimpleTerrain( WO* parentWO, std::string texture, float width, float height, float repeat=1);
      virtual ~MGLSimpleTerrain();
      virtual void render( const Camera& cam );
      virtual void renderSelection(GLubyte red, GLubyte green, GLubyte blue);
   private:
      IndexedGeometryQuad* quad;
   };

}

