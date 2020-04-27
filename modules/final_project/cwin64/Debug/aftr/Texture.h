#pragma once

#include "TextureData.h" //This header file needs to know about GLuint
#include "Vector.h"
#include "Mat4Fwd.h"
#include <string>
#include <iostream>

namespace Aftr
{

/**
   \brief A class that represents a texture that can be bound across
   one or more verticies.

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
   amount, various texture related OpenGL flags (GL_CLAMP_TO_EDGE, GL_REPEAT, GL_CLAMP_TO_BORDER,
   GL_MIRRORED_REPEAT, GL_MIRROR_CLAMP_TO_EDGE), and other attributes
   that change the properties of the texture when it is rendered.
*/
class Texture
{
public:

   friend class ManagerTexture;

   Texture( TextureData* texData );
   Texture( const Texture& tex );
   virtual ~Texture(); //This class is abstract and cannot be instantiated

   /**
      Returns a clone of this instance; behaves identically to proper copy constructor.
      This exists, however, because a copy constructor may be of a base type and accept
      a derived texture. This method enforces that the new'd Texture is always of the
      exact subclass even though a base Texture* is returned.
   */
   virtual Texture* cloneMe() = 0;

   TextureData* getTextureData() const;

   /**
      This resets all properties owned by this Texture Object. This includes resetting
      the this Texture's texture rotation matrix to identity, this Texture's translate
      Vector to (0,0,0), resetting all flags to default values.
   */
   void resetTextureProperties();

   Texture& operator =( const Texture& tex );

   /**
      \return a string containg "FileName:'(fileName)', GLuint:'(glTextureName)'".
   */
   std::string toString() const;

   /// \returns the file name loaded in this texture or "" if not set.
   std::string getFileName() const;

   /// \returns the name of the OpenGL texture. That is, this is the value to use in glBindTexture.
   GLuint getGLTexture() const;

   /**
      This flag remains false until the texture is fully loaded into OGL. Once
      true, this Texture's texData->glTex can be bound and will show 
      the expected texture.
      If this texture is bound before this flag gets set to true, the engine's default
      texture may be displayed but this will not cause undefined behavior.

      This flag is only useful if this texture was loaded via
      ManagerTexture::loadTextureAsync(...); otherwise, this flag gets set to true
      before ManagerTexture::loadTexture(...) returns this object.

      ManagerTexture::loadTextureAsync(...) dispatches a separate thread to load the
      texture so this can be done in parallel.
   */
   bool isTexFullyInitialized() { return this->texData->isTexFullyInitialized(); }

   unsigned int getWidthInPixels() const { return this->texData->getWidthInPixels(); }
   unsigned int getHeightInPixels() const { return this->texData->getHeightInPixels(); }
   bool isMipmapped() { return this->texData->isMipmapped(); }
   bool isUsingTextureMatrix() { return this->UseTexMat; }
   void isUsingTextureMatrix( bool useTexMatrix ) { this->UseTexMat = useTexMatrix; }

   /**
      Enables Texture to be outputted to an ostream.
   */
   friend std::ostream& operator <<( std::ostream&, const Texture& );

   void bind() const;
   void bindGL32() const;
   void bindCompatibility() const;

   void unbind() const;
   void unbindGL32() const;
   void unbindCompatibility() const;

   void getTextureMatrix( float* m4x4ColMajorToPopulate ); ///< Only the current Direction Cosine Matrix (no translations or scalings)
   Mat4 getTextureMatrix(); ///< Only the current Direction Cosine Matrix (no translations or scalings)
   Mat4 getTextureMatrixWithRotScaleAndTrans() const; ///< Full Texture Matrix expected by a Shader
   void setTextureMatrix( const float* const m4x4ColMajorTexMatrix );
   void setTextureMatrix( const Mat4& texMatrix );
   Vector transformVecThroughCurrentTextureMatrix( const Vector& vec );
   Vector transformVecThroughCurrentTextureMatrixAddingCurrentPosition( const Vector& vec );
   Vector transformVecThroughCurrentTextureMatrixSubtractingCurrentPosition( const Vector& vec );
   Vector transformVecThroughInverseOfCurrentTextureMatrix( const Vector& vec );
   Vector transformVecThroughInverseOfCurrentTextureMatrixAddingCurrentPosition( const Vector& vec );
   Vector transformVecThroughInverseOfCurrentTextureMatrixSubtractingCurrentPosition( const Vector& vec );

   void rotateAboutGlobalX( float deltaRadianAngle );
   void rotateAboutGlobalY( float deltaRadianAngle );
   void rotateAboutGlobalZ( float deltaRadianAngle );
   void rotateAboutRelAribitraryAxis( const Vector& axisOfRot, float radianDistance );
   void rotateAboutRelX( float deltaRadianAngle );
   void rotateAboutRelY( float deltaRadianAngle );
   void rotateAboutRelZ( float deltaRadianAngle );
   void rotateAboutGlobalAribitraryAxis( const Vector& axisOfRot, float radianDistance );

   void translateTexture( const Vector& displacement );
   void setTexturePosition( const Vector& position );
   Vector getTexturePosition() const { return this->texTrans; }

   void setTextureRotationPoint( const Vector& rotPointTextureSpace ) { this->fixedPoint = rotPointTextureSpace; }
   void setTextureScaleFactor( const Vector& scaleFactor );
   void scaleTexture( const Vector& deltaScaleToAddToCurrentScaleFactor );
   Vector getTextureScaleFactor() const { return this->texScale; }
   void setTextureRepeatsInX( float numRepeats );
   void setTextureRepeatsInY( float numRepeats );
   void setTextureRepeatsInZ( float numRepeats );
   void setTextureRepeats( float numRepeats );
   void setWrapS( GLint glWrapParam );
   void setWrapT( GLint glWrapParam );

   void setMinFilter( GLenum minFilter );
   void setMagFilter( GLenum magFilter );

   void setEnvMode( GLenum envMode ) { this->envMode = envMode; }

protected:

   /**
      Default constructor is protected so user cannot instantiate without 
      providing more information.
   */
   Texture();


   /**
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
      amount, various texture related OpenGL flags (GL_CLAMP_TO_EDGE, GL_REPEAT, GL_CLAMP_TO_BORDER,
      GL_MIRRORED_REPEAT, GL_MIRROR_CLAMP_TO_EDGE), and other attributes
      that change the properties of the texture when it is rendered.
   */
   TextureData* texData;


   /**
      Per instances data for this Texture Object. This data is owned by this Texture Object.
   */

   float texMat[16]; ///< Texture rotation matrix
   Vector texTrans; ///< Texture translation in X,Y, and Z dimensions
   Vector texScale; ///< Texture scaling in X,Y, and Z dimensions
   Vector fixedPoint; ///< Point about which this texture is rotated
   bool UseTexMat; ///< Iff true, this texture is rotated via this matrix prior to each render; else texMat is not used
   bool UseTexTrans; ///< Iff true, this texture is translated by texTrans vector prior to each render; else texTrans is not used
   bool UseTexScale; ///< Iff true, this texture is scaled by texScale vector prior to each render; else texScale is not used
   
   //Texture OpenGL Flags
   //http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/texparameter.html
   /**
      Sets this texture's environment via glTexEnvi(). (not supported in core)
      This can be set to one of GL_MODULATE, GL_DECAL, GL_BLEND, or GL_REPLACE.
   */
   GLint envMode;
   GLint wrapS; ///< Sets the wrap parameter for texture	coordinate s (u coord) to either GL_CLAMP_TO_EDGE, GL_REPEAT, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_MIRROR_CLAMP_TO_EDGE
   GLint wrapT; ///< Sets the wrap parameter for texture	coordinate t (v coord) to either GL_CLAMP_TO_EDGE, GL_REPEAT, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_MIRROR_CLAMP_TO_EDGE

   /**
      Sets the GL_TEXTURE_MAG_FILTER for magnifying a texel smaller than a pixel up to one pixel.
      Valid values are: GL_NEAREST and GL_LINEAR.
      These are initially set to an intelligent default upon construction and takes
      this texture's mipmapping status into account.
   */
   GLint magFilter;
   
   /**
      Sets the GL_TEXTURE_MIN_FILTER for shrinking a texel bigger than a pixel down to one pixel.
      Valid values are: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
      GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR.
      These are initially set to an intelligent default upon construction and takes
      this texture's mipmapping status into account.
   */
   GLint minFilter;

};

} //namespace Aftr

