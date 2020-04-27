#pragma once

#include "GLSLShader.h"
#include "Vector.h"

namespace Aftr
{

class Camera;
class Model;

class GLSLShaderOVRBarrelDistortion : public GLSLShader
{
public:
   static GLSLShaderOVRBarrelDistortion* New();
   virtual ~GLSLShaderOVRBarrelDistortion();

   GLSLShaderOVRBarrelDistortion& operator =( const GLSLShaderOVRBarrelDistortion& shader );

   /**
      Returns a copy of this instance. This is identical to invoking the copy constructor with
      the addition that this preserves the polymorphic type. That is, if this was a subclass
      of GLSLShader with additional members and methods, this will internally create the
      shader instance as that subclass, thereby preserving polymorphic behavior, members, and
      methods.

      This is in contrast with a copy constructor in the case where one performs:
      GLSLShader* myCopy = new GLSLShader( shaderToBeCopied );
      This will always create a GLSLShader* instance, not a subclass corresponding to the exact
      type of shaderToBeCopied.
   */
   virtual GLSLShader* getCopyOfThisInstance();

   virtual void bind();
   virtual void unbind();

   void setScaleIn( const Vector& scaleIn) { this->scaleIn = scaleIn; }
   void setScale( const Vector& scale ) { this->scale = scale; }
   void setHmdWarpParam( const float p[4] ) { for( int i = 0; i < 4; ++i ) this->hmdWarpParam[i] = p[i]; }
   void setHmdWarpParam( float a, float b, float c, float d ) { this->hmdWarpParam[0] = a; this->hmdWarpParam[1] = b; this->hmdWarpParam[2] = c; this->hmdWarpParam[3] = d; }
   void setScreenCenter( const Vector& center ) { this->screenCenter = center; }
   void setLensCenter( const Vector& lensCenter ) { this->lensCenter = lensCenter; }

   std::string toString();

protected:

   GLSLShaderOVRBarrelDistortion( GLSLShaderDataShared* sharedData );
   GLSLShaderOVRBarrelDistortion( const GLSLShaderOVRBarrelDistortion& toCopy );

   //need distortion coefficients
   Vector scaleIn; ///< Rescale input texture coordinates to [-1,1] unit range,
                   ///< and corrects aspect ratio.
   Vector scale; ///< Rescale output (sample) coordinates back to texture 
                 ///< range and increase scale so as to support sampling outside
                 ///< of the screen
   std::array< float, 4> hmdWarpParam; ///< The array of distortion coefficients
   Vector screenCenter; ///< Texture coordinate for the center of the half-screen
                       ///< texture. This is used to clamp sampling, preventing
                       ///< pixel leakage from one eye view to the other
   Vector lensCenter; ///< Shifts texture coordinates to center the distortion
                      ///< function around the center of the lens

   //float view[16]; ///< view matrix
   //float proj[16]; ///< projection matrix
   //float model[16]; ///< model matrix
   

};

} //namespace Aftr

