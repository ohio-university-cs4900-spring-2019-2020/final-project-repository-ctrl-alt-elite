#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"
#include "Mat4Fwd.h"

namespace Aftr
{
   class Model;

   class GLSLShaderDefaultOrthoStencilGL32 : public GLSLShader
   {
   public:
      static GLSLShaderDefaultOrthoStencilGL32* New();
      virtual ~GLSLShaderDefaultOrthoStencilGL32();
      virtual void bind( const Mat4& MVPMatrix );
      virtual void bind() override;

      GLSLShaderDefaultOrthoStencilGL32& operator=( const GLSLShaderDefaultOrthoStencilGL32& shader );

      virtual void setMVPMatrix( const Mat4& mvpMatrix );      

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
      virtual GLSLShader* getCopyOfThisInstance() override;
   protected:
      GLSLShaderDefaultOrthoStencilGL32( GLSLShaderDataShared* dataShared );
      GLSLShaderDefaultOrthoStencilGL32( const GLSLShaderDefaultOrthoStencilGL32& );
   };
}

