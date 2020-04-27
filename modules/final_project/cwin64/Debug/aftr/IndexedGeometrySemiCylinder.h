#pragma once

#include "IndexedGeometry.h"

namespace Aftr
{

   class IndexedGeometrySemiCylinder : public IndexedGeometry
   {
   public:
      static IndexedGeometrySemiCylinder* New(float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false);
      virtual ~IndexedGeometrySemiCylinder() {}
   protected:
      IndexedGeometrySemiCylinder(float topRadius, float bottomRadius, float height, unsigned int slices, unsigned int stacks, bool useNormals, bool useTextureCoords);
      virtual void createVertices();
      virtual void createIndices();
      virtual void createTextureCoords();
      virtual void createNormals();
      float topRadius;
      float bottomRadius;
      float height;
      unsigned int slices;
      unsigned int stacks;
      bool useNormals;
      bool useTextureCoords;
   };

}

