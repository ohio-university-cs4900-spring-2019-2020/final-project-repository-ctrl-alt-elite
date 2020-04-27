/**
   \class GLSLUniform
   \author Chad Mourning and Scott Nykl
   \brief A wrapper for GLSL Uniforms.
*/

#pragma once

#include "AftrOpenGLIncludes.h"
#include <string>
#ifdef AFTR_CONFIG_USE_OGL_GLEW

namespace Aftr
{

class GLSLShader;

enum GLSLUniformType
{
   utFLOAT = 0,
   utBOOL,
   utINT,
   utVEC2,
   utVEC3,
   utVEC4,
   utBVEC2,
   utBVEC3,
   utBVEC4,
   utIVEC2,
   utIVEC3,
   utIVEC4,
   utMAT2,
   utMAT3,
   utMAT4,
   utIMAGE, //compute shader construct
   utSAMPLER1D,
   utSAMPLER2D,
   utSAMPLER3D,
   utSAMPLERCUBE,
   utSAMPLER1DSHADOW,
   utSAMPLER2DSHADOW,
   utMAX_SHADER_UNIFORM_TYPES
};

class GLSLUniform
{
public:
   /**
   \param name Attribute name
   \param animated If true, update called
   */
   GLSLUniform( const std::string& name, GLSLUniformType type, GLuint programShaderHandle );
   GLSLUniform( const GLSLUniform& toCopy );
   virtual ~GLSLUniform() {}
   GLSLUniform& operator =( const GLSLUniform& u );
   std::string getName() { return uniformName; }
   GLuint getProgramShaderHandle() { return programShaderHandle; }
   virtual void setValues( const float* x );///< sets float values, will crash if x is not of proper length
   virtual void setValues( const int* x );///< sets int values, will crash if x is not of proper length
   virtual void setValues( GLuint x );///< used for sampler uniforms
   virtual void update() {}///< update function, most often used with time
   virtual void updateUniformGLIDfromStringName();
   virtual GLint getUniformHandle() const { return this->uniformNameGLID; }
   virtual GLSLUniformType getUniformType() const { return this->type; }

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
   virtual GLSLUniform* getCopyOfThisInstance();

   /**
      All of the setter variables for the uniform variables
      */
   /**
      sets the uniform for uniform int
      */
   void set(int r);
   /**
      sets the uniform for two ints
      */
   void set(int r, int g);
   void set(int r, int g, int b);
   void set(int r, int g, int b, int a);
   void set(float x);
   void set(float x, float y);
   void set(float x, float y, float z);
   void set(float x, float y, float z, float w);
   void set(bool i);

protected:

   void bindParentProgramShader();
   void unbindParentProgramShader();
   std::string uniformName;
   GLint uniformNameGLID;
   GLuint programShaderHandle;
   GLSLUniformType type;

   GLuint previousShaderPreserverHandle; ///< Used by the bindParentProgramShader and unbindParentProgramShader  

};

}

#endif //AFTR_CONFIG_USE_OGL_GLEW
