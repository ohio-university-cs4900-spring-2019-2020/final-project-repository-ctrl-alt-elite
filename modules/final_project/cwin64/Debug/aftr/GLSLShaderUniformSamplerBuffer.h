#pragma once

#include "GLSLShader.h"

namespace Aftr
{

class Camera;
class Model;

class GLSLShaderUniformSamplerBuffer : public GLSLShader
{
public:
   static GLSLShaderUniformSamplerBuffer* New( const std::string& vertShader, const std::string& fragShader );
   virtual ~GLSLShaderUniformSamplerBuffer();

   GLSLShaderUniformSamplerBuffer& operator =( const GLSLShaderUniformSamplerBuffer& shader );

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
   //void setModel( Model* m ) { this->model = m; }

   virtual void bind();
   virtual void unbind();
   //void setCamera( Camera** cam ) { this->cam = cam; }
   //Camera** getCamera() const { return this->cam; }
   void setDimXY( int x, int y ); ///< Sets size of image in pixels in x,y (horz, vert)
   void getDimXY( int& x, int& y ) const; ///< out param. Size of image in pixels in x,y (horz, vert).
protected:
   GLSLShaderUniformSamplerBuffer( GLSLShaderDataShared* dataShared );
   GLSLShaderUniformSamplerBuffer( const GLSLShaderUniformSamplerBuffer& toCopy );

   void constructShader();
   int xDim;
   int yDim;
};

} //namespace Aftr

