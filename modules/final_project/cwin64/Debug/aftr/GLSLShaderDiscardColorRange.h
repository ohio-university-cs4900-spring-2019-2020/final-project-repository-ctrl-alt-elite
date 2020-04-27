#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"

namespace Aftr
{

class Model;

class GLSLShaderDiscardColorRange : public GLSLShader
{
public:
   static GLSLShaderDiscardColorRange* New( const Vector& color, float epsilon );   
   virtual ~GLSLShaderDiscardColorRange();

   GLSLShaderDiscardColorRange& operator =( const GLSLShaderDiscardColorRange& shader );

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
protected:
   GLSLShaderDiscardColorRange( GLSLShaderDataShared* dataShared, const Vector& color, float epsilon );
   GLSLShaderDiscardColorRange( const GLSLShaderDiscardColorRange& toCopy );
};

}
