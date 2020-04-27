#pragma once

#include "GLSLShader.h"
#include "VectorFwd.h"
#include "Mat4Fwd.h"

namespace Aftr
{
   class Model;

   class GLSLShaderDefaultOrthoWOGUIDepthMapGL32 : public GLSLShader
   {
   public:
      static GLSLShaderDefaultOrthoWOGUIDepthMapGL32* New();
      virtual ~GLSLShaderDefaultOrthoWOGUIDepthMapGL32();
      virtual void bind( const Mat4& MVPMatrix, const ModelMeshSkin& skin );
      virtual void bind() override;

      GLSLShaderDefaultOrthoWOGUIDepthMapGL32& operator=( const GLSLShaderDefaultOrthoWOGUIDepthMapGL32& shader );
     
      virtual void setTex0Matrix( const Mat4& tex0Matrix );
      virtual void setMVPMatrix( const Mat4& mvpMatrix );
      virtual void setMaterialAmbient( const aftrColor4f& materialAmbient );
      virtual void setMaterialDiffuse( const aftrColor4f& materialDiffuse );
      virtual void setMaterialSpecular( const aftrColor4f&  materialSpecular );
      virtual void setSpecularCoefficient( const float specularCoefficient );
      virtual void setCamNear( const float nearPlane );
      virtual void setCamFar( const float farPlane );

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
      GLSLShaderDefaultOrthoWOGUIDepthMapGL32( GLSLShaderDataShared* dataShared );
      GLSLShaderDefaultOrthoWOGUIDepthMapGL32( const GLSLShaderDefaultOrthoWOGUIDepthMapGL32& );
   };
}

