#pragma once

#include "IndexedGeometry.h"
#include "Vector.h"

namespace Aftr
{
   //Indexed Geometry RPrism appears to be "flat shaded" that is to say it contains 24 vertices (4 per face) not 8 (unique vertices)


   class IndexedGeometryRectangularPrism : public IndexedGeometry
   {
   public:
      /// Size is specified as Lx Ly Lz.
      static IndexedGeometryRectangularPrism* New( const Vector& size, bool useNormals = false, bool useTextureCoords = false );
      virtual ~IndexedGeometryRectangularPrism(){};
   protected:
      IndexedGeometryRectangularPrism( const Vector& size, bool useNormals, bool useTextureCoords );
      virtual void createVertices();
      virtual void createIndices();
      virtual void createNormals();
      virtual void createTextureCoords();
      Vector size;
   };

}

