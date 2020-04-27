#pragma once

#include "MGL.h"
#include <string>

namespace Aftr
{

   class IndexedGeometryQuad;
   class IndexedGeometrySphere;
   class IndexedGeometryCylinder;

   class MGLSign : public MGL
   {
   public:      
      MGLSign( WO* parentWO, const std::string& texture, float length, float height, const Vector& color);
      virtual ~MGLSign();
      virtual void render( const Camera& cam );
      virtual bool isInViewingFrustum( const AftrGeometryFrustum& viewportFrustum );
      //virtual void renderSelection(GLubyte red, GLubyte green, GLubyte blue){};
   private:
      float length;
      float height;
      Vector color;
      IndexedGeometryQuad* quad;
      IndexedGeometrySphere* sphere;
      IndexedGeometryCylinder* cylinder;
   };

}

