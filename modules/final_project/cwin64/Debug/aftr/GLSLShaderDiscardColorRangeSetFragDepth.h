#pragma once

#include "GLSLShader.h"
#include "Vector.h"

namespace Aftr
{

class Model;

class GLSLShaderDiscardColorRangeSetFragDepth : public GLSLShader
{
public:
   static GLSLShaderDiscardColorRangeSetFragDepth* New( const Vector& color, float epsilon, float fragDepth );
   virtual ~GLSLShaderDiscardColorRangeSetFragDepth();

   GLSLShaderDiscardColorRangeSetFragDepth& operator =( const GLSLShaderDiscardColorRangeSetFragDepth& shader );

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

   void bind( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, const ModelMeshSkin& skin );

protected:
   GLSLShaderDiscardColorRangeSetFragDepth( GLSLShaderDataShared* dataShared, const Vector& color, float epsilon, float fragDepth );
   GLSLShaderDiscardColorRangeSetFragDepth( const GLSLShaderDiscardColorRangeSetFragDepth& );

   Vector colorRGBtoMatch;
   float epsilon = 0.99f;
   float fragDepth = 0.01f;
};
}

