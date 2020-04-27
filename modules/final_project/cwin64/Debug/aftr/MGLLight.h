#pragma once

#include "MGL.h"

namespace Aftr
{

   class IndexedGeometrySphere;

   class MGLLight : public MGL
   {
   public:
      MGLLight( WO* parentWO );
      virtual ~MGLLight(); 
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   protected:
      IndexedGeometrySphere* sphere;
   };

}  //namespace Aftr

