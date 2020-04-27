#pragma once

#include "AftrOpenGLIncludes.h"
#include <string>

/**
A Uniform Block (a set of uniform(s) stored within a Uniform Buffer Object (UBO)) lets many 
shaders access the same uniform block.
This way many shaders can share a set of common uniforms that only need to be set on the CPU
side once (versus each GLSLUniform inside each GLSLShader having to set the same value multiple times).

For example, instead of each shader having a uniform called ModelViewMatrix, ProjectionMatrix, etc. And
then having to call shader->getUniform(0..n)->setValues( ModelViewMatrix ... Projection Matrix ... ),
we just set them one place in this Uniform Block and let each shader attach to it.
*/

namespace Aftr
{

template <class UNIFORM_BLOCK_STRUCT>
class GLSLUniformBlockT
{
public:

   using value_type = UNIFORM_BLOCK_STRUCT;

   /**
      This first parameter is the string of the uniform block name corresponding to
      that in the shader code. For example, if the shader code says:
      "layout ( binding = 0, std140 ) uniform CameraTransforms", this first param will be
      "CameraTransforms".

      The second parameter is the uniform block binding point at the index specified by the
      binding layout qualifier in the program shader:
      layout (binding = 0, std140 ) uniform CameraTransforms {... } T;

      Each GLSLShader inspects itself for a uniform block which matches the name of the first
      parameter. If found, it will associate its Uniform Block Index with a
      Uniform Block Binding which be the same as the uniformBlockBinding passed in here.
   */
   GLSLUniformBlockT( const std::string& uniformBlockName, GLuint uniformBlockBinding );   
   virtual ~GLSLUniformBlockT();
   GLSLUniformBlockT( const GLSLUniformBlockT& toCopy ) = delete;
   GLSLUniformBlockT& operator =( const GLSLUniformBlockT& ub ) = delete;

   std::string getName() { return uniformBlockName; }
   GLuint getUniformBlockBinding() { return this->uniformBlockBinding; }
   void sendUniformBlockToGL();

   UNIFORM_BLOCK_STRUCT& getBuffer() { return this->buffer; }

protected:
   
   ///< Uniform Block Name of this UniformBlock as defined in the shader program 
   /// EX: given "layout ( binding = 0, std140 ) uniform CameraTransforms", the name
   /// would be "CameraTransforms".
   std::string uniformBlockName = "";
   GLuint uniformBlockBinding = 0; ///< Uniform block binding point at the index specified by the binding layout qualifier in the program shader
   GLuint uboHandle = 0; ///< OpenGL UniformBufferObject handle; this is the GL-side storage (GPU) associated with this uniform block
   
   /// CPU-side buffer which exactly mirrors the std140 layout of the Uniform Block specified in the shader.
   /// This is set to the desired values by the user via the accessor and is subsequently sent to the GPU via sendUniformBlockToGL()
   UNIFORM_BLOCK_STRUCT buffer;
};

} //namespace Aftr

#include "GLSLUniformBlock.cpptemplate.h"
