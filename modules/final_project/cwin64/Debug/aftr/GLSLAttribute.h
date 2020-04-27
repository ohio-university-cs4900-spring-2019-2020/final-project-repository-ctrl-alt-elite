/**
   \class GLSLAttribute
   \author Chad Mourning
   \brief A wrapper for GLSL Attributes.
*/

#pragma once

#ifdef AFTR_CONFIG_USE_OGL_GLEW
#include "AftrOpenGLIncludes.h"
#include <string>

namespace Aftr
{

class GLSLShader;

enum GLSLAttributeType
{
   atFLOAT = 0,
   atBOOL,
   atINT,
   atVEC2,
   atVEC3,
   atVEC4,
   atBVEC2,
   atBVEC3,
   atBVEC4,
   atIVEC2,
   atIVEC3,
   atIVEC4,
   atMAT2,
   atMAT3,
   atMAT4,
   atSAMPLER1D,
   atSAMPLER2D,
   atSAMPLER3D,
   atSAMPLERCUBE,
   atSAMPLER1DSHADOW,
   atSAMPLER2DSHADOW,
   atMAX_SHADER_ATTRIBUTE_TYPES
};

class GLSLAttribute
{
public:
   /**
   \param name Attribute name
   */
   GLSLAttribute( const std::string& name, GLSLAttributeType type, GLSLShader* programShader );
   GLSLAttribute( const GLSLAttribute& toCopy );
   virtual ~GLSLAttribute() { this->programShader = nullptr; }
   GLSLAttribute& operator =( const GLSLAttribute& a );
   std::string getName() { return attributeName; }
   GLSLShader* getParent() { return programShader; }
   void setParent( GLSLShader* parent ) { this->programShader = parent; }
   GLSLAttributeType getAttributeType() { return this->type; }
   GLuint getAttributeLocationInShader() { return this->attributeLocationInShader; }
   //virtual void setValues(float *x);///< sets float values, will crash if x is not of proper length
   //virtual void setValues(int *x);///< sets int values, will crash if x is not of proper length
   virtual void update() {}///< update function, most often used with time

   static GLenum toGLenum( const GLSLAttributeType& t );

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
   virtual GLSLAttribute* getCopyOfThisInstance();

protected:

   //void bindParentProgramShader();
   //void unbindParentProgramShader();

   std::string attributeName;
   GLSLShader* programShader; ///< Not owned, don't delete
   GLSLAttributeType type;
   GLuint attributeLocationInShader;

   GLSLShader* previousShaderPreserver; ///< Used by the bindParentProgramShader and unbindParentProgramShader  

};

}
#endif //AFTR_CONFIG_USE_OGL_GLEW
