#pragma once

#include "MGL.h"

namespace Aftr
{

   class MGLGUIHueLegend : public MGL
   {
   public:
      static MGLGUIHueLegend* New( WO* parent, float height, float width, size_t resolution, float minHue, float maxHue );
      virtual ~MGLGUIHueLegend();
   protected:
      MGLGUIHueLegend( WO* parent );
      virtual void onCreate( float height, float width, size_t resolution, float minHue, float maxHue );
      virtual void render( const Camera& cam );
      size_t resolution;
      float width;
      float height;
      float minHue;
      float maxHue;
   };

}

