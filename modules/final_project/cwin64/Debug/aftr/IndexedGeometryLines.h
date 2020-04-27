#pragma once

#include "IndexedGeometry.h"
#include "AftrGlobals.h"
#include "Vector.h"
#include <vector>

namespace Aftr
{

   class IndexedGeometryLines : public IndexedGeometry
   {
   public:
      /// In passed vectors are NOT owned by this instance, they are only read/copied into graphical data structures during construction.
      /// The caller is still responsible for deleting
      static IndexedGeometryLines* New( const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors );
      virtual ~IndexedGeometryLines(){};
      virtual void render();
      void setVertAtIndex( const Vector& vert, GLsizei idx );
      void setColorAtIndex( const aftrColor4ub& color, GLsizei idx );
      aftrColor4ub getColorAtIndex( GLsizei idx );
      Vector getVertAtIndex( GLsizei idx );
      void setLineWidthInPixels( float lineWidthInPixels ) { this->lineWidthInPixels = lineWidthInPixels; }
      void updateAllLinesAndColorsWithDataExactlyTheSameSize( const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors );

   protected:
      IndexedGeometryLines();
      virtual void init( const std::vector< Vector >& lines, std::vector< aftrColor4ub >* colors );
      virtual void createVertices( const std::vector< Vector >& lines );
      virtual void createVertices() {}
      virtual void createIndices( const std::vector< Vector >& lines );
      virtual void createIndices() {}
      virtual void createColors( std::vector< aftrColor4ub >* colors );

      //used by both createVertices() and resize()
      virtual void assignVertices( const std::vector< Vector >& lines );
      float lineWidthInPixels = 1.0f;
   };

}

