#pragma once

#include "MGL.h"

namespace Aftr
{

class IndexedGeometryQuad;

class MGLOverlayQuad : public MGL
{
public:
   static MGLOverlayQuad* New( WO* parentWO, const std::string& texture, float width, float height );
   static MGLOverlayQuad* New( WO* parentWO, float width, float height );
   virtual ~MGLOverlayQuad();
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
protected:
   MGLOverlayQuad( float width, float height, WO* parentWO );
   virtual void onCreate( const std::string& texture, float width, float height );
   virtual void onCreate( float width, float height );
   virtual void updateBBox();
   float height;
   float width;
   IndexedGeometryQuad* quad;
};

} //namespace Aftr

