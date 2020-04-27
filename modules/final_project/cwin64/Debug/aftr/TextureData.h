#pragma once

#include "AftrOpenGLIncludes.h"
#include <string>
#include <iostream>

namespace Aftr
{

/**
   \brief A class that represents the shared data between a set of textures
   that all render the same raw image data.

   Each Texture object has two parts... Shared data and per instance data. The shared
   data is stored in memory exactly once and is managed by the ManagerTexture; this 
   is the fundamental data that does not ever change regardless of how it is 
   drawn. This includes things like the server side OpenGL handle, the filename 
   corresponding to that data, the actual image data, etc. This is owned 
   by the ManagerTexture and should not be directly manipulated by the user without using 
   the ManagerTexture's functions. This data is stored inside the TextureData Object.
   There is a many-to-one mapping where many Texture Objects map to a single 
   TextureData. A Texture Object has an internal pointer to a TextureData Object.

   The per instance data is unique to this Texture Object and is owned by this Texture Object.
   This includes such things as this Texture Object's texture rotation matrix, texture translate
   amount, various texture related OpenGL flags (GL_CLAMP_TO_EDGE, GL_REPEAT, etc), and other attributes
   that change the properties of the texture when it is rendered.
*/
class TextureData
{
public:

   TextureData();
   TextureData( const TextureData& tex );
   TextureData( const std::string& fileName, GLuint* glTexPtr );
   TextureData( const std::string& fileName );
   TextureData( const GLuint* glTexPtr );
   virtual ~TextureData() = 0;

   //virtual TextureData* cloneMe() = 0;

   TextureData& operator =( const TextureData& tex );

   /**
      \return true iff the file names of both Textures are identical; false, otherwise.
              This method does NOT compare/account for any difference in the OpenGL
              pointers to the texture memory on the graphics card.
   */
   bool operator ==( const TextureData& tex ) const;

   /**
      \return true iff the file names of both Textures are NOT identical; false, otherwise.
              This method does NOT compare/account for any difference in the OpenGL
              pointers to the texture memory on the graphics card.
   */
   bool operator !=( const TextureData& tex ) const;

   /**
      \return true iff the LHS (Left Hand Side) is lexagraphically less 
                   than the RHS (Right Hand Side); false, otherwise.
   */
   bool operator <( const TextureData& tex ) const;

   /**
      \return a string containg "FileName:'(fileName)', GLuint:'(glTextureName)'".
   */
   std::string toString() const;

   /// \returns the file name loaded in this texture or "" if not set.
   std::string getFileName() const;

   /// \returns the name of the OpenGL texture. That is, this is the value to use in glBindTexture.
   GLuint getGLTexture() const;

   void setFileName( const std::string& fileName );
   void setGLTex( GLuint glTex );

   /**
      This flag remains false until the texture is fully loaded into OGL. Once
      true, this TextureData's glTexPtr can be bound and will show the expected texture.
      If this texture is bound before this flag gets set to true, the wrong texture
      may be displayed but this will not cause undefined behavior.

      This flag is only useful if this texture was loaded via
      ManagerTexture::loadTextureAsync(...); otherwise, this flag gets set to true
      before ManagerTexture::loadTexture(...) returns this object.

      ManagerTexture::loadTextureAsync(...) dispatches a separate thread to load the
      texture so this can be done in parallel.
   */
   bool isTexFullyInitialized() { return this->texFullyInitialized; }
   
   /**
      Called by ManagerTexture after this texture is fully loaded. The user should not invoke this.
      The user may invoke TextureData::isTexFullyInitialized() to inspect this value.
   */
   void setTexFullyInitializedState( bool state ) { this->texFullyInitialized = state; }

   /**
      Callbed by ManagerTexture during the texture loading process. The user should not invoke this.
      If the user wants to set the width/height of the image, the user must pass the pixel width
      and pixel height into the ManagerTexture::loadTexture* ( path, width, height). If the height
      and width are left to their default values of 0 in the call to ManagerTexture::loadTexture* (...)
      then the original size of the loaded image will be used.
   */
   void setTextureDimensions( unsigned int widthInPixels, unsigned int heightInPixels );

   /**
      Called by ManagerTexture during the texture loading process. The user should not set this flag
      via this method. If the user wants to create a mipmap of this image, the user must set the
      corresponding flag when calling ManagerTexture::loadTexture* ( ... createMipmap = true ... ).
      If true, a mipmap will be created on server-side (in graphics memory). If false, only the
      image itself will be placed in server-side memory (graphics memory).
   */
   void isMipmapped( bool createMipmapOnLoad ) { this->IsMipmapped = createMipmapOnLoad; }

   unsigned int getWidthInPixels() { return this->width; }
   unsigned int getHeightInPixels() { return this->height; }
   bool isMipmapped() { return this->IsMipmapped; }
   GLenum getTextureDimensionality() { return this->texDimensionality; }
   /// Set to GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_4D, TEXTURE_CUBE_MAP, or TEXTURE_BUFFER_EXT; default is 2D.
   void setTextureDimensionality( GLenum texDimensionality ) { this->texDimensionality = texDimensionality; }
   bool isSameDimensionAsFile() { return this->IsSameDimensionAsFile; }
   void isSameDimensionAsFile( bool usingOriginalDimensions ) { this->IsSameDimensionAsFile = usingOriginalDimensions; }

   /**
      Specifies the number of color components in the texture. Defaults to GL_RGBA. After this 
      texture has been loaded in memory according to this format, this value is not used by GL.
      Must be 1, 2, 3, or 4, or one of the 
      following symbolic constants: GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, 
      GL_COMPRESSED_ALPHA, GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, 
      GL_COMPRESSED_INTENSITY, GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_DEPTH_COMPONENT, 
      GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_LUMINANCE, GL_LUMINANCE4, 
      GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4, 
      GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, GL_LUMINANCE12_ALPHA12, 
      GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4, GL_INTENSITY8, GL_INTENSITY12, 
      GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, 
      GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16, 
      GL_SLUMINANCE, GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, GL_SRGB8, 
      GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.
   */
   void setGLInternalFormat( GLint internalFormat ) { this->internalFormat = internalFormat; }
   GLint getGLInternalFormat() { return this->internalFormat; }

   /**
      Specifies the format of the pixel data. When the raw pixel/texel data is loaded from an 
      image format, this param tells OpenGL how that raw data is ordered. After this texture is 
      loaded, this value is no longer used by GL. Defaults to GL_RGBA.

      Specifies the format of the pixel data. The following symbolic values are accepted: 
      GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, 
      GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
   */
   void setGLRawTexelFormat( GLenum format ) { this->format =  format; }
   GLenum getGLRawTexelFormat() { return this->format; }

   /**
      Specifies the data type of the pixel data. This specifies the sizes of the raw pixel / 
      texel data channels determined by GLenum format (this->format). After this texture 
      has been loaded, this value is not used by GL. Defaults to GL_UNSIGNED_BYTE.

      The following symbolic values are accepted: 
      GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, 
      GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, 
      GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, 
      GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, 
      GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.
   */
   void setGLRawTexelType( GLenum type ) { this->type = type; }
   GLenum getGLRawTexelType() { return this->type; }

   /**
      Enables TextureData to be outputted to an ostream.
   */
   friend std::ostream& operator <<( std::ostream&, const TextureData& );

protected:

   /**
      This flag remains false until the texture is fully loaded into OGL. Once
      true, this TextureData's glTexPtr can be bound and will show the expected texture.
      If this texture is bound before this flag gets set to true, the wrong texture
      may be displayed but this will not cause undefined behavior.

      This flag is only useful if this texture was loaded via
      ManagerTexture::loadTextureAsync(...); otherwise, this flag gets set to true
      before ManagerTexture::loadTexture(...) returns this object.

      ManagerTexture::loadTextureAsync(...) dispatches a separate thread to load the
      texture so this can be done in parallel.
   */
   bool texFullyInitialized = false;
   std::string fileName; ///< name of texture read from disk
   GLuint glTex; ///< Actual GLuint handle to server-side texture on graphics card, this is used w/ glBindTexture
   unsigned int width; ///< Width of Image in pixels (0 means unknown)
   unsigned int height; ///< Height of Image in pixels (0 means unknown)
   bool IsMipmapped; ///< If true, this image is mipmapped on server-side; false if not mipmapped on server-side
   GLenum texDimensionality; ///< Set to GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_4D, TEXTURE_CUBE_MAP, or TEXTURE_BUFFER_EXT; default is 2D.
   bool IsSameDimensionAsFile; ///< True iff, this texture was loaded from a file and has the same dimensions as the raw data in that file.

   /**
      Defaults to GL_RGBA. After this texture has been loaded, this value is not used by GL.

      Specifies the number of color components in the texture. Must be 1, 2, 3, or 4, or one of the 
      following symbolic constants: GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, 
      GL_COMPRESSED_ALPHA, GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_LUMINANCE_ALPHA, 
      GL_COMPRESSED_INTENSITY, GL_COMPRESSED_RGB, GL_COMPRESSED_RGBA, GL_DEPTH_COMPONENT, 
      GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT32, GL_LUMINANCE, GL_LUMINANCE4, 
      GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16, GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4, 
      GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, GL_LUMINANCE12_ALPHA12, 
      GL_LUMINANCE16_ALPHA16, GL_INTENSITY, GL_INTENSITY4, GL_INTENSITY8, GL_INTENSITY12, 
      GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, 
      GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16, 
      GL_SLUMINANCE, GL_SLUMINANCE8, GL_SLUMINANCE_ALPHA, GL_SLUMINANCE8_ALPHA8, GL_SRGB, GL_SRGB8, 
      GL_SRGB_ALPHA, or GL_SRGB8_ALPHA8.
   */
   GLint internalFormat; 
    
   /**
      Defaults to GL_RGBA. When the raw pixel/texel data is loaded from an image format, this param
      tells OpenGL how that raw data is ordered. After this texture is loaded, this value is no longer
      used by GL.

      Specifies the format of the pixel data. The following symbolic values are accepted: 
      GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, 
      GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
   */
   GLenum format;
   
   /**
      Defaults to GL_UNSIGNED_BYTE. This specifies the sizes of the raw pixel / texel data channels
      determined by GLenum format (this->format). After this texture has been loaded, this value
      is not used by GL.

      Specifies the data type of the pixel data. The following symbolic values are accepted: 
      GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, 
      GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, 
      GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, 
      GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, 
      GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.
   */
   GLenum type;

};

/// Output function be-friended by TextureData class
std::ostream& operator <<( std::ostream&, const TextureData& );

} //namespace Aftr

