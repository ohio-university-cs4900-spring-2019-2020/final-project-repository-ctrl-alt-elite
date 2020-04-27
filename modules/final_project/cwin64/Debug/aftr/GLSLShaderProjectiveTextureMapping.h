#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"
#include "Mat4Fwd.h"

namespace Aftr
{
   class Model;

   class GLSLShaderProjectiveTextureMapping : public GLSLShader
   {
   public:
      static GLSLShaderProjectiveTextureMapping* New( const std::string& vertPath = "", const std::string& fragPath = "" );
      virtual ~GLSLShaderProjectiveTextureMapping();
      virtual void bind( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, const ModelMeshSkin& skin );

      GLSLShaderProjectiveTextureMapping& operator=( const GLSLShaderProjectiveTextureMapping& shader );

      virtual void setModelMatrix( const Mat4& modelMatrix );
      virtual void setNormalMatrix( const Mat4& normalMatrix );
      virtual void setTex0Matrix( const Mat4& tex0Matrix );
      virtual void setMVPMatrix( const Mat4& mvpMatrix );
      virtual void setProjectorMatrix( const Mat4& projectorMatrix );

      virtual void setMaterialAmbient( const Vector& materialAmbient );
      virtual void setMaterialDiffuse( const Vector& materialDiffuse );
      virtual void setMaterialSpecular( const Vector& materialSpecular );
      virtual void setSpecularCoefficient( const float specularCoefficient );


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
      GLSLShaderProjectiveTextureMapping( GLSLShaderDataShared* dataShared );
      GLSLShaderProjectiveTextureMapping( const GLSLShaderProjectiveTextureMapping& );
   };
}

