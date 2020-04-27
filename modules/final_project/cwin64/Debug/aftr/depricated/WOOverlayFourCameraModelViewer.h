#pragma once

#include "WO.h"
using namespace std;

namespace Steamie
{
   class SteamieFBOUserSpecifiedRenderTarget;

   class WOOverlayFourCameraModelViewer : public WO
   {
   public:
      static WOOverlayFourCameraModelViewer* New( WO* woToView );
      virtual ~WOOverlayFourCameraModelViewer();
      virtual void onUpdateWO();
   protected:
      WOOverlayFourCameraModelViewer( WO* modelToView );
      virtual void onCreate();
      SteamieFBOUserSpecifiedRenderTarget* fbo;
      Texture* xTex;
      Texture* yTex;
      Texture* zTex;
      WO* modelToView;//this model is what it will focus on
   };

}

