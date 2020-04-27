#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"

namespace Aftr
{

class Model;

class GLSLShaderCUDAWaterFFT : public GLSLShader
{
public:
   static GLSLShaderCUDAWaterFFT* New( float heightScale, float chopiness, float size, Vector shallowColor, Vector deepColor, Vector skyColor );
   virtual ~GLSLShaderCUDAWaterFFT();

   GLSLShaderCUDAWaterFFT& operator =( const GLSLShaderCUDAWaterFFT& shader );

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
   void setModel( Model* m ) { this->model = m; }

   virtual void bind();
   virtual void unbind();
protected:
   GLSLShaderCUDAWaterFFT( GLSLShaderDataShared* dataShared, float heightScale, float chopiness, float size, Vector shallowColor, Vector deepColor, Vector skyColor );
   GLSLShaderCUDAWaterFFT( const GLSLShaderCUDAWaterFFT& );

   Model* model = nullptr; ///< Not owned, do not delete

};

}
