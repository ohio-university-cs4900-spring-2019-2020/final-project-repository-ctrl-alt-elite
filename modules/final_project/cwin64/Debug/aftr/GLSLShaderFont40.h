#pragma once

#include "GLSLShaderDefaultGL32.h"
#include "VectorFwd.h"
#include "Mat4Fwd.h"

namespace Aftr
{
   class Model;

   class GLSLShaderFont40 : public GLSLShader
   {
   public:
      static GLSLShaderFont40* New();
      virtual ~GLSLShaderFont40();
      //virtual void bind(const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam);
      virtual void bind(const Mat4& modelMatrix, const Camera& cam);

      GLSLShaderFont40& operator=(const GLSLShaderFont40& shader);

      virtual void setModelMatrix(const Mat4& modelMatrix, const Camera& cam);

      virtual void setColor(const aftrColor4f& color);

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
      GLSLShaderFont40(GLSLShaderDataShared* dataShared);
      GLSLShaderFont40(const GLSLShaderFont40&);
   };
}

