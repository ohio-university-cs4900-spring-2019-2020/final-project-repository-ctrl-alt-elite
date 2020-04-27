#pragma once

#include "GLSLShader.h"

namespace Aftr
{
      class Model;

   class GLSLShaderDefaultSelectionGL32 : public GLSLShader
   {
   public:
      static GLSLShaderDefaultSelectionGL32* New();
      virtual ~GLSLShaderDefaultSelectionGL32();
      virtual void bind( const Mat4& MVPMatrix, GLubyte red, GLubyte green, GLubyte blue );
      void setSelectionColor( GLubyte red, GLubyte green, GLubyte blue );

      GLSLShaderDefaultSelectionGL32& operator=( const GLSLShaderDefaultSelectionGL32& shader );

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
      GLSLShaderDefaultSelectionGL32( GLSLShaderDataShared* dataShared );
      GLSLShaderDefaultSelectionGL32( const GLSLShaderDefaultSelectionGL32& );
   };
}

