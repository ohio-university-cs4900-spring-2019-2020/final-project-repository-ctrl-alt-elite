#pragma once

#include "MGL.h"

namespace Aftr
{
   class IndexedGeometryQuad;
   class WO;

   class MGLBillboardAllAxes : public MGL
   {
   public:
      virtual ~MGLBillboardAllAxes();
      static MGLBillboardAllAxes* New( WO* parent, float height, float width );
   protected:
      virtual void onCreate();
      MGLBillboardAllAxes( WO* parent, float height, float width );
      virtual void render( const Camera& cam );
      IndexedGeometryQuad* quad;

   };

}

