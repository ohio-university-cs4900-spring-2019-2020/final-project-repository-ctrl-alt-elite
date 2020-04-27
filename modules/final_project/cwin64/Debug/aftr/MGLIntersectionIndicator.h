#pragma once

#include "MGL.h"

namespace Aftr
{
   class WOIntersectionIndicator;

   class MGLIntersectionIndicator : public MGL
   {
   public:
      MGLIntersectionIndicator(WOIntersectionIndicator* parent);
      virtual ~MGLIntersectionIndicator(){};
      virtual void render( const Camera& cam );
      virtual void renderSelection(GLubyte red, GLubyte green, GLubyte blue);
      bool binary;
   protected:
      WOIntersectionIndicator* parent;
   };
}

