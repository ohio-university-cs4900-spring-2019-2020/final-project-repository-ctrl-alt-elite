#pragma once

#include "MGL.h"
#include "Mat4Fwd.h"

namespace Aftr
{

class IndexedGeometryQuad;
class AftrFrameBufferObject;
class Font;

class MGLGUIDepthMap : public MGL
{
public:
   static MGLGUIDepthMap* New( WO* parentWO, Texture* depthBufferTexture, float width, float height, 
                       std::string onPanelHasFocusTex = "" );
   static MGLGUIDepthMap* New( WO* parentWO, float width, float height );
   virtual ~MGLGUIDepthMap();

   /// The near plane used when the depth texture was rendered (used to linearize the non-linear depth buffer).
   /// It is assumed this depth map was generated using a perspective projection matrix.
   /// This populates the GLSLShaderDefaultOrthoWOGUIDepthMapGL32 shader's uniform "CamNear" on the shader's bind().
   void setNearPlaneForDepthTexture( float camNearPlane ) { this->CamNear = camNearPlane; }

   /// The far plane used when the depth texture was rendered (used to linearize the non-linear depth buffer).
   /// It is assumed this depth map was generated using a perspective projection matrix.
   /// This populates the GLSLShaderDefaultOrthoWOGUIDepthMapGL32 shader's uniform "CamFar" on the shader's bind().
   void setFarPlaneForDepthTexture( float camFarPlane ) { this->CamFar = camFarPlane; }

   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

   virtual void resizeQuad( float newWidthAbs, float newHeightAbs );

   /**
      Used by GUI objects to modify the stencil buffer to clip to this widget to its
      parent's dimensions. 
      
      If true is passed in as the first argument, the stencil buffer will 
      INCREMENT its stencil values where this widget's dimensions intersect 
      with its parents dimensions. This is used during the pre-render phase
      during the depth first traversal down the GUI tree to ensure all 
      widgets are properly clipped.

      If false is passed in as the first argument, the stencil buffer will 
      DECREMENT its stencil values where this widget's dimensions intersect 
      with its parents dimensions. This is used during the post-render phase
      during the depth first traversal up the GUI tree to restore the stencil
      buffer to the same state as when this node was first encountered. This way
      other branches are not affected by this branch of the tree manipulating
      the stencil buffer.
   */
   virtual void updateStencilBoundingQuad( bool stencilOpINCorDEC, GLubyte red = 255, GLubyte green = 255, GLubyte blue = 255 );
   AftrFrameBufferObject* getFBO();

   /**
      Called by root node when beginning a GUI render
   */
   virtual void setStencilBufferToAllOnes( const Mat4& projMat );

   void isUsingShearMatrix( bool useShearMatrix );
   bool isUsingShearMatrix();
   void updateShearMatrix( float roll, float aspectRatioWidthToHeight );

   /**
      When set to true, this widget is stencilled (clipped) by parents bounding volume.
      This is true by default. To opt out of using the stencil buffer, set this to false.
   */
   virtual void isUsingStencilBuffer( bool useStencilBufferForClipping );
   virtual bool isUsingStencilBuffer() { return this->IsUsingStencilBuffer; }

protected:
   MGLGUIDepthMap( float width, float height, WO* parentWO, std::string onPanelHasFocusTex = "" );
   virtual void onCreate( Texture* depthBufferTexture );
   virtual void onCreate();
   virtual void updateBBox();
   virtual void setupSkinShader();

   float height = 0.25f;
   float width = 0.25f;
   IndexedGeometryQuad* quad = nullptr;
   ModelMeshSkin hasFocusSkin; ///< Skin bound to quad when rendering the hasFocus border around widget

   bool IsUsingStencilBuffer = true; ///< True by default. When true, this widget is stencilled (clipped) by parents bounding volume

   Mat4 shearMat;
   bool IsUsingShearMatrix = false;

   float CamNear = 1.0; ///< The near plane used when the depth texture was rendered (used to linearize the non-linear depth buffer)
   float CamFar = 1000.0f; ///< The far plane used when the depth texture was rendered (used to linearize the non-linear depth buffer)
};

} //namespace Aftr


