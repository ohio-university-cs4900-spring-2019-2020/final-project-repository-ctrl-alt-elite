#pragma once

#include "GLSLShader.h"

namespace Aftr
{
      class Model;

   class GLSLShaderDiscardAlphaRange : public GLSLShader
   {
   public:
      static GLSLShaderDiscardAlphaRange* New( float alpha, float epsilon );

      //GLSLShaderDiscardAlphaRange( float alpha, float epsilon  );
      virtual ~GLSLShaderDiscardAlphaRange();

      GLSLShaderDiscardAlphaRange& operator =( const GLSLShaderDiscardAlphaRange& shader );

      void setEpsilon( float epsilon );
      void setAlphaDiscardRange( float alphaDiscardRange );

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
      GLSLShaderDiscardAlphaRange( GLSLShaderDataShared* dataShared, float alpha, float epsilon );
      GLSLShaderDiscardAlphaRange( const GLSLShaderDiscardAlphaRange& );

      GLSLUniform* ualpha;
      GLSLUniform* uepsilon;
   };
}

