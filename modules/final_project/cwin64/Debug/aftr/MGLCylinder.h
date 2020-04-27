#pragma once

#include "MGL.h"

namespace Aftr
{
   class IndexedGeometryCylinder;
   class IndexedGeometryDisc;

   class MGLCylinder : public MGL
   {
   public:
      static MGLCylinder* New(WO* parent, float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false);
      virtual ~MGLCylinder();
      virtual void render( const Camera& cam );
      IndexedGeometryCylinder* getCylinderIndexedGeometry() { return this->cylinder; }
      IndexedGeometryDisc* getCylinderTopCapIndexedGeometry() { return this->topCap; }
      IndexedGeometryDisc* getCylinderBottomCapIndexedGeometry() { return this->bottomCap; }
   protected:
      MGLCylinder(WO* parent, float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false);
      virtual void onCreate();
      IndexedGeometryCylinder* cylinder;
      IndexedGeometryDisc* topCap;
      IndexedGeometryDisc* bottomCap;
      float height;
   };

}

