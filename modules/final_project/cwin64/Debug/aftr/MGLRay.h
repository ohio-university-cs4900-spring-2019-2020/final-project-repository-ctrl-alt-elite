#pragma once

#include "MGL.h"

namespace Aftr
{

class WORay;

class MGLRay : public MGL
{
public:
   MGLRay( WORay* parent );
   virtual ~MGLRay();
   virtual void render( const Camera& cam );
protected:
   WORay* parent;
   VertexListEntryGL_V3F va[2];
   GLubyte indicies[2];

};

} //namespace Aftr

