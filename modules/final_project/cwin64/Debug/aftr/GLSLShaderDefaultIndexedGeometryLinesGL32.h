#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"
#include "Mat4Fwd.h"

namespace Aftr
{
   class Model;

   class GLSLShaderDefaultIndexedGeometryLinesGL32 : public GLSLShader
   {
   public:
      static GLSLShaderDefaultIndexedGeometryLinesGL32* New();
      virtual ~GLSLShaderDefaultIndexedGeometryLinesGL32();
      virtual void bind( const Mat4& MVPMatrix );

      //This bind method implements the standard bind(...) parameter list expected when ModelMeshSkin.bind() calls bind on its associated shader.
      virtual void bind( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, const ModelMeshSkin& skin );

      GLSLShaderDefaultIndexedGeometryLinesGL32& operator=( const GLSLShaderDefaultIndexedGeometryLinesGL32& shader );

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
      virtual GLSLShader* getCopyOfThisInstance();
   protected:
      GLSLShaderDefaultIndexedGeometryLinesGL32( GLSLShaderDataShared* dataShared );
      GLSLShaderDefaultIndexedGeometryLinesGL32( const GLSLShaderDefaultIndexedGeometryLinesGL32& );
   };
}

