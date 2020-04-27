#pragma once

#include "MGL.h"

namespace Steamie
{

   class MGLOverlayFourCameraModelViewer : public MGL
   {
   public:
      static MGLOverlayFourCameraModelViewer* New( WO* parent );
      virtual ~MGLOverlayFourCameraModelViewer();
      virtual void render( const Camera& cam );
   protected:
      MGLOverlayFourCameraModelViewer( WO* parent );
      virtual void onCreate();
   };

}

