#pragma once

#include "IndexedGeometry.h"

namespace Aftr
{

   class IndexedGeometrySphereTriStrip : public IndexedGeometry
   {
   public:
      static IndexedGeometrySphereTriStrip* New( float radius = 1, unsigned int numCols = 4, unsigned int numRows = 4, bool useNormals = false, bool useTextures = false );
      virtual ~IndexedGeometrySphereTriStrip() {}
   protected:
      IndexedGeometrySphereTriStrip( float radius = 1, unsigned int numCols = 4, unsigned int numRows = 4, bool useNormals = false, bool useTextures = false );
      virtual void createVertices();
      virtual void createIndices();
      virtual void createTextureCoords();
      virtual void createNormals();
      float radius = 1.0f;
      unsigned int numCols;
      unsigned int numRows;
   };

}

