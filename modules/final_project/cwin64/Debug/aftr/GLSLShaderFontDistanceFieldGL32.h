#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"
#include "Mat4Fwd.h"

namespace Aftr
{
   class Model;

   class GLSLShaderFontDistanceFieldGL32 : public GLSLShader
   {
   public:
      static GLSLShaderFontDistanceFieldGL32* New();
      virtual ~GLSLShaderFontDistanceFieldGL32();
      virtual void bind( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, const ModelMeshSkin& skin ) override;
      virtual void bind() override;

      GLSLShaderFontDistanceFieldGL32& operator=( const GLSLShaderFontDistanceFieldGL32& shader );

      virtual void setModelMatrix( const Mat4& modelMatrix );
      virtual void setNormalMatrix( const Mat4& normalMatrix );
      virtual void setTex0Matrix( const Mat4& tex0Matrix );
      virtual void setMVPMatrix( const Mat4& mvpMatrix );      

      virtual void setMaterialAmbient( const aftrColor4f& materialAmbient );
      virtual void setMaterialDiffuse( const aftrColor4f& materialDiffuse );
      virtual void setMaterialSpecular( const aftrColor4f&  materialSpecular );
      virtual void setSpecularCoefficient( const float specularCoefficient );

      virtual void setFontColor( const aftrColor4f& fontColor );


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
      GLSLShaderFontDistanceFieldGL32( GLSLShaderDataShared* dataShared );
      GLSLShaderFontDistanceFieldGL32(const GLSLShaderFontDistanceFieldGL32&);
      aftrColor4f color;
   };
}

