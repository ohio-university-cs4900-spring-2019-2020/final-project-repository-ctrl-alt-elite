#pragma once

#include "IndexedGeometry.h"

namespace Aftr
{

   class IndexedGeometryDisc : public IndexedGeometry
   {
   public:
      static IndexedGeometryDisc* New(float innerRadus = 1, float outerRadius = 0, unsigned int slices = 5, bool useNormals = false, bool useTextures = false);
      virtual ~IndexedGeometryDisc() {}
   protected:
      IndexedGeometryDisc(float innerRadus, float outerRadius, unsigned int slices, bool useNormals, bool useTextures);
      virtual void createVertices();
      virtual void createIndices();
      virtual void createNormals();
      virtual void createColors();
      virtual void createTextureCoords();
      float innerRadius;
      float outerRadius;
      unsigned int slices;
   };

}

