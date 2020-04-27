#pragma once

#include "MGL.h"

namespace Aftr
{
   class IndexedGeometrySemiCylinder;
   class IndexedGeometryDisc;

   class MGLSemiCylinder : public MGL
   {
   public:
      MGLSemiCylinder* New(WO* parent, float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false);
      MGLSemiCylinder(WO* parent, float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false);
      virtual ~MGLSemiCylinder();
      virtual void render( const Camera& cam );
   protected:
      virtual void onCreate();
      IndexedGeometrySemiCylinder* cylinder;
      //IndexedGeometryDisc* topCap;
      //IndexedGeometryDisc* bottomCap;
      float height;
   };

}

