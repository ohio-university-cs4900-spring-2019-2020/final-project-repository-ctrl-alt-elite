#pragma once

#include "MGL.h"

namespace Aftr
{ 
   class IndexedGeometryQuad;
   class MGLCountdown : public MGL
   {
   public:
      MGLCountdown( WO* parentWO, std::vector<std::string> slides );
      virtual ~MGLCountdown();
      virtual void render( const Camera& cam );     
      void setCurrentScaleOfSlide(float x){currentScaleOfSlide =  x;}
      void incrementTextureIndex(){this->useNextSkin();}
   private:     
     float currentScaleOfSlide;
     IndexedGeometryQuad* quad;
   };
}

