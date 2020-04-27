#pragma once

#include "MGL.h"

namespace Aftr
{
   class MGLCameraSink : public MGL
   {
   public:
      static MGLCameraSink* New(WO* parent, float width, float height );
      virtual ~MGLCameraSink();
      virtual void render( const Camera& cam );
      WO* getParent() { return parent; }
      virtual void initOpenGL() {}
   protected:
      MGLCameraSink(WO* parent, float width, float height);
      void makeVBO();
      WO* parent;
      float height;
      float width;
   };
}

