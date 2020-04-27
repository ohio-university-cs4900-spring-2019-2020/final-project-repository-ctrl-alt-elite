#pragma once

#include "MGL.h"

namespace Aftr
{
class IndexedGeometryAxes;
class GLSLShaderDefaultIndexedGeometryLinesGL32;

class MGLAxes : public MGL
{
public:
   MGLAxes( WO* parentWO, Vector lengths, float lineWidthInPixels );
   virtual ~MGLAxes();
   virtual void render( const Camera& cam );
   virtual void renderGL32( const Camera& cam );
   virtual void renderCompatibility( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   virtual void renderSelectionCompatibility( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   virtual void renderSelectionGL32( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   virtual void setLineWidth( float lineWidthInPixels ) { this->lineWidthInPixels = lineWidthInPixels; }
   virtual float getLineWidth() { return this->lineWidthInPixels; }

protected:
   Vector lengths;
   IndexedGeometryAxes* axes = nullptr;
   float lineWidthInPixels = 1.0f;
};
}

