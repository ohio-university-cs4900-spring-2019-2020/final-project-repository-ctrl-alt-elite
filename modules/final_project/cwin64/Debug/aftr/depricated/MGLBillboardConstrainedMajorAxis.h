#pragma once

#include "MGL.h"

namespace Aftr
{

   class IndexedGeometryQuad;

   class MGLBillboardConstrainedMajorAxis : public MGL
   {
   public:
      MGLBillboardConstrainedMajorAxis(WO* parentWO, const std::string& texturePath, WO* source, WO* sink, Camera** cam, float width );
      virtual ~MGLBillboardConstrainedMajorAxis();
      virtual void render( const Camera& cam );
      void setLightWaveWidth( float width );
      float getLightWaveWidth();

   protected:
      WO* source;
      WO* sink;
      float width;
      Camera** cam;
      IndexedGeometryQuad* quad;
   };

} //namespace Aftr

