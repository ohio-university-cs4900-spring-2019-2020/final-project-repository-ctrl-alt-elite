#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_OGL_GLEW

#include "AftrFrameBufferObject.h"

namespace Aftr
{
class ModelMesh;
class AftrFBOTargetBillboardInfo;

class AftrFBOUserSpecifiedRenderTarget : public AftrFrameBufferObject
{
public:
   static AftrFBOUserSpecifiedRenderTarget* New( bool useDepthBuffer = false, 
                                                 bool storeDepthBufferAsGLTexture = false,
                                                 bool useAntiAliasing = false );

   virtual ~AftrFBOUserSpecifiedRenderTarget();

   ///calling this function will involve binding this FBO, so a currently bound FBO (including this one) will become unbound
   void setRenderTarget( GLuint renderTarget, size_t width = 1, size_t height = 1, 
                         bool useDepthBuffer = true, bool useStencilBuffer = false );

   void resizeCurrentTarget( size_t width, size_t height, bool useDepthBuffer = true, bool useStencilBuffer = false );

   /**
      Takes the WO's bounding box, projects it into screen space to get the SSLxLy and SSCenterPoint.
      Using SSLxLy and SSCenterPoint, the target's dimensions are resized to SSLxLy. Finally, the 
      target is rendered into using only the pixels inside the screen space bounding box of the
      wo (via gluPickMatrix).
   */
   virtual void renderToCurrentTargetResizingTargetToScreenSpaceBoundingBoxOfWO( 
      WO* wo, Camera* cam, bool useDepthBuffer, bool useStencilBuffer, bool renderFrameToScreen,
      AftrFBOTargetBillboardInfo* outBillBoardInfo = NULL );

   virtual bool renderToCurrentTargetResizingTargetToScreenSpaceBoundingBoxOfMesh( 
      ModelMesh* mesh, Camera* cam, bool useDepthBuffer, bool useStencilBuffer, bool renderFrameToScreen,
      AftrFBOTargetBillboardInfo* outBillBoardInfo = NULL );

   virtual void renderToCurrentTargetResizingTargetToScreenSpaceBoundingBoxOfWOCachingIntermediateResults( 
      WO* wo, Camera* cam, bool useDepthBuffer, bool useStencilBuffer, bool renderFrameToScreen,
      AftrFBOTargetBillboardInfo* outBillBoardInfo = NULL );

   virtual bool renderToCurrentTargetResizingTargetToScreenSpaceBoundingBoxOfMeshCachingIntermediateResults( 
      ModelMesh* mesh, Camera* cam, bool useDepthBuffer, bool useStencilBuffer, bool renderFrameToScreen,
      AftrFBOTargetBillboardInfo* outBillBoardInfo = NULL );

protected:
   AftrFBOUserSpecifiedRenderTarget( bool useDepthBuffer, bool storeDepthBufferAsGLTexture, bool useAntiAliasing );
   //return true if a change was made, false otherwise
   bool adjustCombinedBufferResize(bool useDepthBuffer, bool useStencilBuffer);
   bool adjustDepthBufferResize(bool useDepthBuffer, bool useStencilBuffer);
   bool adjustStencilBufferResize(bool useDepthBuffer, bool useStencilBuffer);
   bool adjustNoBufferResize(bool useDepthBuffer, bool useStencilBuffer );
   bool adjustRenderTargetResize(bool useDepthBuffer, bool useStencilBuffer );

   bool adjustCombinedBufferNoResize(bool useDepthBuffer, bool useStencilBuffer);
   bool adjustDepthBufferNoResize(bool useDepthBuffer, bool useStencilBuffer);
   bool adjustStencilBufferNoResize(bool useDepthBuffer, bool useStencilBuffer);
   bool adjustNoBufferNoResize(bool useDepthBuffer, bool useStencilBuffer );
   bool adjustRenderTargetNoResize(bool useDepthBuffer, bool useStencilBuffer );

   bool originalHandleInUse;
};

}

#endif
