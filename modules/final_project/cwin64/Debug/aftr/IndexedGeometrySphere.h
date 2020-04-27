#pragma once

#include "IndexedGeometry.h"

namespace Aftr
{

   class IndexedGeometrySphere : public IndexedGeometry
   {
   public:
      static IndexedGeometrySphere* New(float radius = 1, unsigned int slices = 4, unsigned int stacks = 4, bool useNormals = false, bool useTextures = false);
      virtual ~IndexedGeometrySphere() {}
   protected:
      IndexedGeometrySphere( float radius = 1, unsigned int slices = 4, unsigned int stacks = 4, bool useNormals = false, bool useTextures = false);
      virtual void createVertices();
      virtual void createIndices();
      virtual void createTextureCoords();
      virtual void createNormals();
      float radius;
      unsigned int slices;
      unsigned int stacks;
   };

}

