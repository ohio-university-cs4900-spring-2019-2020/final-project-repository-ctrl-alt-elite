#pragma once
#include "MGLGrid.h"

namespace Aftr
{   class MGLGridLinesRegular2D : public MGLGrid
   {
   public:
      static MGLGridLinesRegular2D* New( WO* parentWO, float xDim, float xGranularity, float yDim, float yGranularity, 
         const aftrColor4ub& color = aftrColor4ub( 255,255,255,255 ) );
      virtual ~MGLGridLinesRegular2D();
      virtual void defineVertices();
      virtual void defineIndices();
      virtual void makeVBO(int splits = 0);
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
      virtual void render( const Camera& cam );
      virtual void setGlLineWidth( float GlLineWidth ) {this->GlLineWidth = GlLineWidth; }
      virtual float getGlLineWidth() { return this->GlLineWidth; }
   protected:
      MGLGridLinesRegular2D( WO* parentWO );
      virtual void onCreate( float xDim, float xGranularity, float yDim, float yGranularity, const aftrColor4ub& color );
      float xDim;
      float yDim;
      float xGranularity; 
      float yGranularity;
      float GlLineWidth;
   };

}

