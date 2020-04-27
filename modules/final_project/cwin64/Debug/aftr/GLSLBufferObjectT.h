#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_OGL_GLEW
#include "AftrOpenGLIncludes.h"
#include "AftrUtilities.h"

namespace Aftr
{

/**
   \author Scott Nykl
   \brief Encapsulates functionality described by OpenGL 4.3 Buffer Objects (Section 6 of 4.3 compat spec doc)
*/

template <class T>
class GLSLBufferObjectT
{
public:

   /**
      bufferObjectBindingLoc specifies the 'binding' name/location of the buffer object. This is the integer
      name used in the shader binding, for example. (binding=2 says the binding location is 2).
      layout( std430, binding=2 ) buffer MyData {...} myDat;

      program shader handle defines the GL name of the GLSL program.

      target specifies the Buffer Object Type / Targe; ie, GL_SHADER_STORAGE_BUFFER, GL_UNIFORM_BUFFER, 
      GL_TEXTURE_BUFFER, etc (4.3 GL Spec Table 6.1 Buffer Object Binding Targets).
   */
   GLSLBufferObjectT( GLenum  target, GLuint bufferObjectBindingLoc, GLuint programShaderHandle );
   virtual ~GLSLBufferObjectT();

   virtual void bind();
   virtual void unbind();

   GLuint getBufferHandle() { return this->bufferObjectHandle; }
   GLenum getTarget() { return this->target; }
   GLuint getBindingLocation() { return this->bufferBindingLoc; }
   T getBuffer() { return T; }

protected:

   GLenum target; ///< Buffer Object type, ie, GL_SHADER_STORAGE_BUFFER, GL_UNIFORM_BUFFER, 
                  ///< GL_TEXTURE_BUFFER, etc (4.3 GL Spec Table 6.1 Buffer Object Binding Targets)

   GLuint bufferObjectHandle; ///< GL's given name for this buffer object
   GLuint bufferBindingLoc; ///< The binding layout unit associated with this buffer object within the shader

   T buffer; ///< Template defined buffer; usually a data struct matching that of the GLSL Compute shader

};

} //namespace Aftr

#include "GLSLBufferObjectT.cpptemplate.h"

#endif
