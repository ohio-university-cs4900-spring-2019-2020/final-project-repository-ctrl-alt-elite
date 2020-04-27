#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_OGL_GLEW
#pragma once
#include <vector>
#include <stack>
#include <string>
#include "AftrOpenGLIncludes.h"
#include "Texture.h"


namespace Aftr
{
   class Camera;
   class WO;
   class WorldContainer;

class AftrFBOState
{
public:
   AftrFBOState( unsigned int width, unsigned int height, GLuint handle );
   virtual ~AftrFBOState();
   std::string toString();
   unsigned int width;
   unsigned int height;
   GLuint handle;
};

   /**
   \author Chad Mourning and Scott Nykl
   */

class AftrFrameBufferObject
{
public:
   /***
      Creates a new FBO of the given width and height. 
      numTextures: number of color textures associated with this FBO
      useDepthBuffer: if TRUE, creates and updates a depth buffer. This can either be stored internally 
                      as a GL Render Buffer or as a more flexible, but possibly slower GL Texture 
                      (depending on usage), see input variable storeDepthBufferAsGLTexture.
                      if FALSE, no depth buffer is allocated or updated. No depth information may be 
                      retrieved.
      useStencilBuffer: if TRUE, creates and updates a stencil buffer. Always stored as a render buffer.
                      if FALSE, no stencil buffer is allocated or updated. No stencil information may be
                      retrieved.
      useAntiAliasing: if TRUE, uses a NVIDIA specific MSAA (multi-sampling Anti-aliasing) extension.
                       if FALSE, no Aftr specific AA is enabled, the driver configuration may optionally
                       perform AA.
      storeDepthBufferAsGLTexture: if TRUE, (and useDepthBuffer is true) stores the depth buffer as a GL texture 
                                   that may be accessed via:
                                   AftrFrameBufferObject::generateTextureFromFBODepthMapOwnsTexDataSharesGLHandle().
                                   This is useful, for example, if the user would like to pass the depth buffer as a texture
                                   to the compute shader to use.
                                   if FALSE, (and useDepthBuffer is false) stores the depth buffer as a 
                                   GL render buffer. GL render buffer may be supported on older hardware and may
                                   be slightly faster in some circumstances (texture filtering, etc); however, the 
                                   depth information will not be easily accessible to the programmer.
   **/
   static AftrFrameBufferObject* New( unsigned int width, unsigned int height, unsigned int numTextures = 1,
                                         bool useDepthBuffer = true, bool useStencilBuffer = false, 
                                         bool useAntiAliasing = false, 
                                         bool storeDepthBufferAsGLTexture = false );
   
   void updateAttachments( unsigned int width, unsigned int height, unsigned int numTextures = 1, bool useDepthBuffer = true, bool useStencilBuffer = false);
   //uses the same FBO Handle, but changes the texture attachment size, as well as depth and stencil attachments if applicable
   void adjustFBOSize( unsigned int width, unsigned int height );
   
   virtual ~AftrFrameBufferObject();

   ///prepares the fbo for rendering by binding the fbo and setting the viewport according
   //to the in passed parameters.
   void bind( GLint xStart, GLint yStart, GLuint width, GLuint height );
   
   ///prepares the fbo for rendering by binding the fbo and setting the viewport according to the
   //current size of the current target.
   void bind();
   ///unbind will unbind the buffer and pop the attribute stack, therefore, do NOT call unbind without calling bind first
   ///By default, unbind will also regenerate the corresponding mipmaps to the bound render target, pass in false
   ///To this method to skip regeneration of mipmaps
   void unbind( bool updateMipmaps = true );
   GLuint* getTextureHandles() { return textureHandles; }
   /// Returns a texture which owns its TextureData. The Texture's TextureData, however, does not own (shares with this FBO object) its GLTex handle
   Texture* generateTextureFromFBOTextureOwnsTexDataSharesGLHandle();
   /// Returns a texture wrapping the depth buffer associated with this FBO. NULL is returned if no depth buffer is associated.
   Texture* generateTextureFromFBODepthMapOwnsTexDataSharesGLHandle();
   /// Returns a texture which shares (does not own) its TextureData. The Texture's TextureData, however, owns (does not share) its GLTex handle
   Texture* generateTextureFromFBOTextureSharesTexDataOwnsGLHandle();
   void bindMyTexture();///< binds this fbos textureHandles[0] to GL_TEXTURE_2D
   void unbindMyTexture();///< binds 0 to GL_TEXTURE_2D
   std::string toString(); ///< Returns a string containing info about this FBO

   /// Render the current wo from the perspective of cam. The output is rendered into the currently bound target.
   virtual void renderToCurrentTarget( WO* wo, Camera& cam, bool renderFrameToScreen = false, 
                                       bool clearColorDepthStencilBuffersPriorToRender = true );
   virtual void renderToCurrentTarget( WorldContainer& wo, Camera& cam, bool renderFrameToScreen = false,
                                       bool clearColorDepthStencilBuffersPriorToRender = true,
                                       bool usePerspectiveProjectionForNonWOGUIObjects = true,
                                       bool automaticallyInvokeSetupSingleCameraImmediatelyPriorToRender = true );

   /**
      This method returns true iff an FBO is currently bound. If true, the out parameters for width and height,
      in pixels, are set to the width and height (in pixels) of the currently bound target.
      If no FBO is currently bound, false is returned, and the out parameters are not touched.
   */
   static bool hasTargetCurrentlyBound( int& outTargetWidth, int& outTargetHeight );

   aftrColor4f& getClearColor() { return this->fboClearColor; }

   void validateFBO();

   unsigned int getWidthPixels() { return this->width; }
   unsigned int getHeightPixels() { return this->height; }

   /**
      Outputs the contents of the renderbuffer to the file
   */
   void toFile( const std::string& filename );

   GLuint getDepthBufferGLID();

protected:
   AftrFrameBufferObject( unsigned int width, unsigned int height, unsigned int numTextures, 
                             bool useDepthBuffer, bool useStencilBuffer, 
                             bool useAntiAliasing, bool storeDepthBufferAsGLTexture );
   virtual void onCreate();

   aftrColor4f fboClearColor;

   unsigned int width;
   unsigned int height;
   GLuint handle; ///< FBO handle created by glGenFrameBuffers
   //stuff used for FBO's renderToTexture
   GLuint* textureHandles;
   unsigned int numTextures;

   //depth buffer stuff
   bool hasDepthBuffer;
   GLuint depthBufferHandle; ///< Depth Buffer, if enabled, is rendered into as a texture OR as a render buffer, depending on this.storeDepthBufferAsGLTexture
   bool storeDepthBufferAsGLTexture; ///< if true, this.depthBufferHandle is a GL_TEXTURE2D handle. If false, this.depthBufferHandle is a glRenderBufferStorage
   
   //stencil buffer stuff
   bool hasStencilBuffer;
   GLuint stencilBufferHandle; ///< Stencil Buffer, if enabled, is rendered into a Render Buffer (not a texture)
   
   //antialiasing buffer stuff
   bool hasAntialiasBuffer;
   GLuint aaFBHandle; ///< Anti-alias Frame Buffer for multisampling
   GLuint aaColorRB; ///< Anti-alias Color Render Buffer handle
   GLsizei aaNumSamples = 16; ///< Number of AntiAliasing samples 2x, 4x, 8x, 16x, 32x
   GLenum aaInternalColorFormat = GL_RGBA8; ///< Defaults to GL_RGBA8
   GLenum aaInternalDepthFormat = GL_DEPTH24_STENCIL8; ///< Defaults to GL_DEPTH24_STENCIL8


   void attachDepthBuffer();
   void attachStencilBuffer();
   void attachCombinedDepthStencilBuffer();
   void attachOutputTexture(unsigned int numTextures);
   bool attachAntiAliasBuffer();

   void adjustTextureSize( );
   void adjustDepthSize( );
   void adjustStencilSize( );
   void adjustCombinedDepthStencilSize( );

   //functions for adjusting existing attachments
   void convertCombinedBufferToDepthOnly();
   void convertCombinedBufferToStencilOnly();
   void convertAntiAliasedBufferToCombined();
   

   void detachDepthOnly();//deletes attachment and sets component to null
   void detachStencilOnly();//delets attachment and sets component to null
   void detachCombined();
   void detachAntiAliasBuffer();

   void reMipmapRenderTargets();

   static std::stack< AftrFBOState > fboAttribStack; ///< Stack used to save multiple binds
};

#endif

}

