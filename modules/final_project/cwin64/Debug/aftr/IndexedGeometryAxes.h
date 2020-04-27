#pragma once

#include "IndexedGeometry.h"
#include "Vector.h"

namespace Aftr
{

class IndexedGeometryAxes : public IndexedGeometry
{
public:
   static IndexedGeometryAxes* New( float size );
   static IndexedGeometryAxes* New( const Vector& lengths );
   virtual ~IndexedGeometryAxes() {}
protected:
   IndexedGeometryAxes( const Vector& axes );
   virtual void createVertices();
   virtual void createIndices();
   virtual void createColors();
   Vector lengths;
};

}

