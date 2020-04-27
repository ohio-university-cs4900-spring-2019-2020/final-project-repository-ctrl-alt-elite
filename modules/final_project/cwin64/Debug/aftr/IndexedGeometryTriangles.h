#pragma once

#include "IndexedGeometry.h"
#include "AftrGlobals.h"
#include "Vector.h"
#include <vector>

namespace Aftr
{

   class IndexedGeometryTriangles : public IndexedGeometry
   {
   public:
      /// In passed vectors are NOT owned by this instance, they are only read/copied into graphical data structures during construction.
      /// The caller is still responsible for deleting
      static IndexedGeometryTriangles* New( const std::vector< Vector >& vertexList, 
                                            const std::vector< unsigned int >& indexList );
      static IndexedGeometryTriangles* New( const std::vector< Vector >& vertexList, 
                                            const std::vector< unsigned int >& indexList,
                                            const std::vector< aftrColor4ub >& colors );
      virtual ~IndexedGeometryTriangles(){};
      virtual void render();
      //void setVertAtIndex( const Vector& vert, GLsizei idx );
      //void setColorAtIndex( const aftrColor4ub& color, GLsizei idx );
      //aftrColor4ub getColorAtIndex( GLsizei idx );
      //Vector getVertAtIndex( GLsizei idx );
      //void setLineWidthInPixels( float lineWidthInPixels ) { this->lineWidthInPixels = lineWidthInPixels; }
      //void updateAllLinesAndColorsWithDataExactlyTheSameSize( const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors );

   protected:
      IndexedGeometryTriangles();
      virtual void init( const std::vector< Vector >& vertexList, const std::vector< unsigned int >& indexList, 
                         const std::vector< aftrColor4ub >& colors );
      virtual void createVertices( const std::vector< Vector >& lines );
      virtual void createVertices() {}
      virtual void createIndices( const std::vector< unsigned int >& lines );
      virtual void createIndices() {}
      virtual void createColors( const std::vector< aftrColor4ub >& colors );

      //used by both createVertices() and resize()
      //virtual void assignVertices( const std::vector< Vector >& lines );
   };

}

