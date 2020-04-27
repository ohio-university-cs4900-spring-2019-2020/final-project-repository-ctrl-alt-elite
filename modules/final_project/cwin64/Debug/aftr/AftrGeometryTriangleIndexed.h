#pragma once

#include <vector>
#include <string>
#include "VectorFwd.h"

namespace Aftr
{

//template< typename T > class VectorT;


class AftrGeometryTriangleIndexed
{
   public:
      AftrGeometryTriangleIndexed( const std::vector< Vector >& vertexList );
      AftrGeometryTriangleIndexed( int vertA, int vertB, int vertC, const std::vector< Vector >& vertexList );
      AftrGeometryTriangleIndexed( const AftrGeometryTriangleIndexed& toCopy );
      ~AftrGeometryTriangleIndexed();
      AftrGeometryTriangleIndexed& operator= ( const AftrGeometryTriangleIndexed& triangle );
      int& operator() ( int indexOfVertex ); ///< myTri(x) = 3; //Assign index of 3 the xth point of this triangle
      int operator() ( int indexOfVertex ) const; ///< int val = myFace(x); //Get index into composite vertex list from this triangle
      const std::vector< Vector >& getVertexList() const;
      std::string toString() const;

   protected:
      // Index into this Octree's vertList
      int a; ///< Index of first vertex of this triangle
      int b; ///< Index of second vertex of this triangle
      int c; ///< Index of third vertex of this triangle
      /**
         Pointer to vertex list. int a,b,c are indicies into this list. This list is NOT owned by
         this object. This list is never modified by this object.
      */
      const std::vector< Vector >& verts;

};


} //namespace Aftr

