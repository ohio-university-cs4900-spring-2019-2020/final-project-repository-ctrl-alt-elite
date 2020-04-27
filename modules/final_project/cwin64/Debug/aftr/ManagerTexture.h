#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <deque>

#include "AftrOpenGLIncludes.h"
#include "AftrGlobals.h"
#include "Texture.h"
#include "TextureData.h"
#include "TextureOwnsTexData.h"
#include "TextureOwnsTexDataSharesGLHandle.h"
#include "TextureOwnsTexDataOwnsGLHandle.h"
#include "TextureDataOwnsGLHandle.h"
#include "TextureSharesTexData.h"
#include "TextureSharesTexDataOwnsGLHandle.h"
#include "TextureDataSharesGLHandle.h"

struct SDL_Surface;

namespace boost { class mutex; }

namespace Aftr
{

class GLView;
class WO;
class Model;
class MGL;
class WorldList;
class Texture;

struct TextureSetCompare
{
   bool operator() ( const TextureDataOwnsGLHandle* lhs, const TextureDataOwnsGLHandle* rhs ) const
   { return ( (*lhs) < (*rhs) ); }
};

class ManagerTexture
{
public:	
   
   static size_t getNumberOfTextures() { return textures.size(); }
   static unsigned int getTotalTextureMemoryUsedInBytes() { return totalBytesOfTextureMemoryUsed; }
   static std::string toString();
   static Texture* getDefaultTexture() { return DEFAULT_TEXTURE_PTR->cloneMe(); }
   static GLuint getDefaultTextureID() { return DEFAULT_TEXTURE_PTR->getGLTexture(); }
   static Texture* getDefaultWhite2x2Texture() { return DEFAULT_WHITE_2X2_PTR->cloneMe(); }

   static void init();

   /**
      Deletes all TextureDataOwnsGLHandle objects loaded via ManagerTexutre::loadTexture()
      and ManagerTexture::loadTextureAsync(). This removes all corresponding server
      side texture memory as well.

      After this method finishes, all memory allocated by this manager is free'd.
   */
   static void shutdown();

   /**
      Loads a texture from an image file. Supports .jpg, .tga, .png,
      and .bmp. The user does NOT own this pointer and should NOT delete it.
      This manager ensures a texture is loaded exactly once, and duplicate
      requests simply receive a pointer to the original texture.

      pixelWidth will resize the final image width in graphics memory (server side) to be that many pixels wide.
      This value defaults to zero, which means do not resize the input image width.

      pixelHeight will resize the final image height in graphics memory (server side) to be that many pixels tall.
      This value defaults to zero, which means do not resize the input image height.

      If createMipmap is true, a set of subsampled images are automatically generated and will increase
      rendering speed at the cost of twice the amount of texture memory as the original image.
      If createMipmap is false, only the loaded image is placed in graphics memory (server side).
      createMipmap defaults to true, enabling mipmapping for fileToLoad.

      internalFormat
         Specifies the number of color components in the texture. Must be 1, 2, 3, or 4, or one of the 
         following symbolic constants: GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, 
         GL_COMPRESSED_ALPHA, GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, 
         GL_COMPRESSED_INTENSITY, GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_DEPTH_COMPONENT, 
         GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_LUMINANCE, 
         GL_LUMINANCE4, GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, 
         GL_LUMINANCE4_ALPHA4, GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, 
         GL_LUMINANCE12_ALPHA12, GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4, GL_INTENSITY8, 
         GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB10, 
         GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, 
         GL_RGBA16, GL_SLUMINANCE, GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, 
         GL_SRGB8, GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.

      format
         Specifies the format of the pixel data. The following symbolic values are accepted: 
         GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA, 
         GL_BGRA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.

      type
         Specifies the data type of the pixel data. The following symbolic values are accepted: 
         GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, 
         GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, 
         GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, 
         GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, 
         GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.

      \return A pointer to the texture loaded in memory. The user
              does NOT own this pointer and should NOT delete it.
   */
   static Texture* loadTexture( const std::string& fileToLoad, unsigned int pixelWidth = 0, unsigned int pixelHeight = 0, bool createMipmap = true,
            GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE );

   #ifdef AFTR_CONFIG_USE_BOOST
      /**
         Asynchronous version of ManagerTexture::loadTexture(...). This
         behaves the same as above, except execution returns before the
         texture is fully loaded. The returned TextureDataOwnsGLHandle object will have
         its TextureDataOwnsGLHandle::isTexFullyInitialized() return false until the texture
         has completely finished loading. Once loading has completely finished
         TextureDataOwnsGLHandle::isTexFullyInitialized() will return true and the TextureDataOwnsGLHandle's
         corresponding GLuint* handler will point to the valid 
         server-side texture.

         pixelWidth will resize the final image width in graphics memory (server side) to be that many pixels wide.
         This value defaults to zero, which means do not resize the input image width.

         pixelHeight will resize the final image height in graphics memory (server side) to be that many pixels tall.
         This value defaults to zero, which means do not resize the input image height.

         If createMipmap is true, a set of subsampled images are automatically generated and will increase
         rendering speed at the cost of twice the amount of texture memory as the original image.
         If createMipmap is false, only the loaded image is placed in graphics memory (server side).
         createMipmap defaults to true, enabling mipmapping for fileToLoad.

         internalFormat
            Specifies the number of color components in the texture. Must be 1, 2, 3, or 4, or one of the 
            following symbolic constants: GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, 
            GL_COMPRESSED_ALPHA, GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, 
            GL_COMPRESSED_INTENSITY, GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_DEPTH_COMPONENT, 
            GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_LUMINANCE, 
            GL_LUMINANCE4, GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, 
            GL_LUMINANCE4_ALPHA4, GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, 
            GL_LUMINANCE12_ALPHA12, GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4, GL_INTENSITY8, 
            GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB10, 
            GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, 
            GL_RGBA16, GL_SLUMINANCE, GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, 
            GL_SRGB8, GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.

         format
            Specifies the format of the pixel data. The following symbolic values are accepted: 
            GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA, 
            GL_BGRA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.

         type
            Specifies the data type of the pixel data. The following symbolic values are accepted: 
            GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, 
            GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, 
            GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, 
            GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, 
            GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.

         \return A pointer to the texture loaded in memory. The user
                 does NOT own this pointer and should NOT delete it.
      */
      static Texture* loadTextureAsync( const std::string& fileToLoad, unsigned int pixelWidth = 0,
         unsigned int pixelHeight = 0, bool createMipmap = true,
         GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE );

      /**
         After the asynchronous version of prepareTextureForOpenGLInstantiation()
         completes texture loading, that texture must be sent server-side. This
         is most efficiently done using only one thread. This method will send
         pending textures to server-side via invocation of 
         instantiateOpenGLTexture().

         To ensure the running module maximizes performance, we do not want to
         send all pending textures at once as this could take a noticable amount
         of time. Therefore, a periodic scheduler that will send a few textures each
         iteration is used.
      */
      static unsigned int sendPendingAsyncTexturesToGfxMemoryViaScheduledTimer();
      static unsigned int sendPendingAsyncTexturesToGfxMemoryViaForceAllNow();
   #endif

   /**
      Returns a texture that is completely owned by the caller. This type of texture
      is expected to be manipulated by Frame Buffer Objects (FBOs) for rendering to a 
      texture, or other more advanced usages beyond a simply texture loaded from a file.

      The user is responsible for deleting this Texture and its TextureDataShared as well.
   */
      static TextureOwnsTexDataOwnsGLHandle* loadDynamicTexture( GLenum textureTarget = GL_TEXTURE_2D,
         GLint level = 0, unsigned int pixelWidth = 1, unsigned int pixelHeight = 1,
         GLint internalFormat = GL_RGBA, GLint border = 0,
         GLenum rawTexelFormat = GL_RGBA, GLenum rawTexelType = GL_UNSIGNED_BYTE, 
         const GLvoid* pixels = NULL );

   static void bindTexture( Texture* tex, GLenum mode = GL_TEXTURE_2D );

   /**
      This method will remove the pointed at texture from the ManagerTexture's cache as well as the
      OpenGL buffers residing on the GPU. The user must ensure all references /data point to this
      texture are no longer used as all handles / values / references / pointers to this texture
      become invalid.

      This method is expected to be passed in ONLY textures that were
   */
   static bool deleteTextureFromCPUandGPU( Texture* tex );

protected:

   /**
      This method initializes a default 2x2 white texture (RGBA = 255). This read-only texture is used when an 
      "empty" texture is needed. For example, in the GLSLShaderDefaultGL32 shader, a texture must always be
      bound to perform phong shading and texture blending. However, many objects do not have textures loaded 
      for them upon their creation (such as many IndexedGeometry objects).

      To facilitate these indexed geometries rendering properly even though their corresponding skin has no texture, this
      texture is used in its place. A copy of this texture is used as the "default" texture when a ModelMeshSkin is created.
      This copy is placed in ModelMeshSkin::getMultiTextureSet[0] during the ModelMeshSkin's construction if no other texture
      is provided.
   */
   static void initWhite2x2Texture();

   /**
      This method takes the raw image data in the desired OpenGL format and
      then generates an actual OpenGL TextureDataOwnsGLHandle (glGenTex), it then sends the
      texture parameters and finally builds a mipmapped image and sends it
      server side. NOTE: If OpenGL ES is used, a mipmap is not generated,
      in this case, only a single resolution texture is sent to the graphics
      card.

      One invocation of this method attempts to retrieve exactly one queued
      TextureDataOwnsGLHandle from the ManagerTexture::texturesToSendToOpenGL list and
      instantiate that TextureDataOwnsGLHandle in OpenGL as described above. If this succeeds
      properly, true is returned, false, otherwise.

      If a TextureDataOwnsGLHandle point is passed in, that exact texture is retreived from
      the list and instantiated; otherwise false is returned.
   */
   static bool instantiateOpenGLTexture( TextureDataOwnsGLHandle* tex = NULL );

   /**
      This methods opens the texture's image from file, (.jpg, .png, .bmp, etc)
      creates a local client-side texture that is all ready to be sent to the
      server-side via glGenTex, glTexImage2D, gluBuild2DMipmaps, etc. This method
      does not make any OpenGL calls nor does it depend on the OpenGL state,
      therefore, this method can be run asynchronously without affecting the
      GL context.

      If this method returns true, the processed image and the corresponding
      TextureDataOwnsGLHandle object pair has been inserted into ManagerTexture::texturesToSendToOpenGL.
      Invoking a call to


      \return true if the image was successfully processed and is ready to be
      placed server-side.
   */
   static bool prepareTextureForOpenGLInstantiation( TextureDataOwnsGLHandle* tex, unsigned int pixelWidth, unsigned int pixelHeight );

   /**
      Helper function used inside of ManagerTexture::prepareTextureForOpenGLInstantiation(...).
      By default SDL_Image assumes position (0,0) refers to the upper left corner of the image.
      Unfortunately, OpenGL assumes position (0,0) refers to the lower left corner of the image.
      As a result, after SDL_Image loads the desired image file, the image's internal data must
      be flipped so the images appear properly when rendered as OpenGL Textures.

      SDL_Surface* image is not modified by this method.
      
      If this method fails to flip the image, NULL is returned.
      If this method succeeds, this method returns a newly allocated SDL_Surface containing
      the flipped image. The user owns this new surface and is responsible for destroying it.
   */
   static SDL_Surface* convertSDLImageCoordsToOpenGLTexCoords( SDL_Surface* image ); 

   /** 
      Finds smallest power of 2 value larger than or equal to input)
      \return Smallest power of 2 larger than or equal to input.
   */
   static int powerOfTwo(int input);

   /**
      Set containing all textures that have been loaded via 
      ManagerTexture::loadTexture( const std::string& fileName ). These textures
      are owned and managed by this Manager. The user should not directly delete
      any TextureDataOwnsGLHandle*. All textures are loaded exactly once and may be referenced by
      many different Models and/or ModelData objects.
   */
   static std::set< TextureDataOwnsGLHandle*, TextureSetCompare > textures;
   
   #ifdef AFTR_CONFIG_USE_BOOST
   static boost::mutex* texturesMutex; ///< Semaphore protecting ManagerTexture::textures
   #endif

   /**
      Populated by prepareTextureForOpenGLInstantiation() and emptied by
      instantiateOpenGLTexture().
   */
   static std::deque< std::pair< TextureDataOwnsGLHandle*, SDL_Surface* > > texturesToSendToOpenGL;

   #ifdef AFTR_CONFIG_USE_BOOST
   static boost::mutex* texturesToSendToOpenGLMutex;///< Semaphore protecting ManagerTexture::texturesToSendToOpenGL
   static boost::mutex* invokeSDLFunctionMutex;///< Semaphore protecting multiple async texture loading threads from async stomping SDL Functions
   #endif

   /** 
      Default texture used by the engine. This default is ALWAYS returned in the
      event of ManagerTexture::loadTexture(...) failing to find/load the specific
      file. The engine loads the default texture at start up; if the default texture
      cannot be loaded, the engine will give an error and not load.
   */
   static Texture* DEFAULT_TEXTURE_PTR;

   /**
      A Default 2x2 white texture (RGBA = 255). This read-only texture is used when an "empty" texture is needed. For example,
      in the GLSLShaderDefaultGL32 shader, a texture must always be bound to perform phong shading and texture blending.
      However, many objects do not have textures loaded for them upon their creation (such as many IndexedGeometry objects).

      To facilitate these indexed geometries rendering properly even though their corresponding skin has no texture, this
      texture is used in its place. A copy of this texture is used as the "default" texture when a ModelMeshSkin is created.
      This copy is placed in ModelMeshSkin::getMultiTextureSet[0] during the ModelMeshSkin's construction if no other texture
      is provided.
   */
   static Texture* DEFAULT_WHITE_2X2_PTR; 

	/**
      individual texture information used for when creating individual glTexturePtrs
   */
	static std::string DEFAULT_TEXTURE; //Path to default concrete texture

   /**
      Number of byte used to store all textures that are loaded. This value assumes
      textures are mipmapped (each texture then occupies twice the amount of memory
      as would be needed otherwise).
   */
   static unsigned int totalBytesOfTextureMemoryUsed;

   /**
      Checks the status of the framebuffer to make sure there are no errors.
      This function will only print errors, but will continue to allow for the program to run
   */
   #ifdef AFTR_CONFIG_USE_OGL_GLEW
      static void checkFrameBufferStatus();
   #endif

   /**
         Image loader for iPhone.

         Uses SDL_Bitmap if a .bmp
         Uses Objective-C Core Graphics .png loader if a png
   */
   #ifdef AFTR_CONFIG_USE_IPHONE
      static SDL_Surface* IMG_Load_iPhone( char* filename);
   #endif

};

}
