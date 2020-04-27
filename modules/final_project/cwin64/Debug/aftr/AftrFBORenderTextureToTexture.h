#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_OGL_GLEW

#include "AftrFrameBufferObject.h"

namespace Aftr
{
   class WOGUI;
   class WorldList;
   class Texture;
   class CameraStandardEZNav;

   class AftrFBORenderTextureToTexture : public AftrFrameBufferObject
   {
   public:
      static AftrFBORenderTextureToTexture* New();

      virtual ~AftrFBORenderTextureToTexture();

      virtual Texture* generateTextureFromFBOTextureOwnsTexDataSharesGLHandle( unsigned int width, unsigned int height );
      ///calling this function will involve binding this FBO, so a currently bound FBO (including this one) will becone unbound
      void setRenderTarget( GLuint renderTarget, size_t width, size_t height );
      void setRenderSource( Texture* srcTex );
      void resizeCurrentTarget( size_t width, size_t height );
      virtual void renderToCurrentTarget();


   protected:
      AftrFBORenderTextureToTexture();

      virtual void onCreate();

      //return true if a change was made, false otherwise
      bool adjustCombinedBufferResize(bool useDepthBuffer, bool useStencilBuffer);
      bool adjustDepthBufferResize(bool useDepthBuffer, bool useStencilBuffer);
      bool adjustStencilBufferResize(bool useDepthBuffer, bool useStencilBuffer);
      bool adjustNoBufferResize(bool useDepthBuffer, bool useStencilBuffer );
      

      bool adjustCombinedBufferNoResize(bool useDepthBuffer, bool useStencilBuffer);
      bool adjustDepthBufferNoResize(bool useDepthBuffer, bool useStencilBuffer);
      bool adjustStencilBufferNoResize(bool useDepthBuffer, bool useStencilBuffer);
      bool adjustNoBufferNoResize(bool useDepthBuffer, bool useStencilBuffer );

      WOGUI* quad;
      WorldList* woList;
      Texture* srcTexture;
      CameraStandardEZNav* orthoCam;


      bool adjustRenderTargetResize();

      bool originalHandleInUse;
   };

}

#endif
