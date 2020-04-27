#pragma once

#include "ModelMeshLOD.h"
#include "Vector.h"
#include "AftrOpenGLIncludes.h"


namespace Aftr
{

   class Camera;
   class Texture;
   class AftrFBOUserSpecifiedRenderTarget;
   class TextureOwnsTexDataOwnsGLHandle;
   class IndexedGeometryQuad;
   class GLSLShader;

   class MMLODBillboardNonCentered : public ModelMeshLOD
   {
   public:
      MMLODBillboardNonCentered( ModelMesh* parentMesh, Camera** camPtr, AftrFBOUserSpecifiedRenderTarget* fboTexGen );
      virtual ~MMLODBillboardNonCentered();
      virtual void onUpdateLOD();
      virtual void onFullUpdateLOD();
      /// Renders the billboard representing this mesh
      virtual void render( const Camera& cam );
      /// Renders the parent's mesh's geometry/skin/etc into the currently bound buffer.
      /// This is called by generateTexture() in order to render the parent mesh onto a texture.
      virtual void renderMeshForTextureGeneration( const Camera& cam );
      virtual ModelMeshLOD* cloneMe();
      virtual void updateTextureRotation();
      void useTextureRotation( bool useTexRot );
      bool useTextureRotation();

      //virtual float getHarwaveletError();
      //virtual float getJarrodError();
      //virtual float getLevinsteinError();


      //find cleaner way to do this
      void incrementSizeOfTextureAndScale( const Vector& increment );

      void useTextureFace( bool useTexFace );
      bool useTextureFace();

      bool hasValidTextureFromLastTexGeneration() { return this->HasValidTextureFromLastTexGeneration; }

	   GLfloat* getTransformedVertices();
   GLfloat* getTightVertices( int& size );

	  Vector getOffset() { return bbOffset; }
   TextureOwnsTexDataOwnsGLHandle* getTex() { return tex; }


   protected:
	   Camera* cameraAtTimeOfGeneration;///< camera at the time of generation
  // Vector originalCameraPosition; ///< Original position of the camera when the texture was generated, in case information is needed later
  // float originalCameraOrientation[16]; ///< Original orientation of the camera when texture was generated, in case information is needed later

      Camera** camPtr; ///< Camera* pointer of the camera from which the scene is rendered; not owned, do not delete
      AftrFBOUserSpecifiedRenderTarget* fbo; ///< FBO used to generate texture; not owned, do not delete
      TextureOwnsTexDataOwnsGLHandle* tex; ///< Texture populated by FBO, owned by this instance
      IndexedGeometryQuad* quad; ///< Quad upon which this.tex (generated by this.fbo) is placed for rendering
      GLSLShader* discardShader; ///< Shader used to discard fragments who's texture coordinates are outside [0,1].
      Vector bbOffset; ///< Offset from MeshPos when converted from the SS axis aligned center

      float m[16]; ///< current Model Matrix of this Billboard, updated each render
      float t[16]; ///< texture matrix computed as the transform which solves Ax=b (for x), where A is this.m (known), x is this.t (unknown), and b is this.r (known).
      float r[16]; ///< Model Matrix of this Billboard when this.tex was last generated (oRiginal)

      //bool updateInitialOrientMatrix; ///< Set to true when this.tex is regenerated, so this.r gets set to the 'new' oRiginal matrix
      bool useTexRot; ///< When true, the texture bound when invoking this.render will use the computed texture display matrix to mitigate LOD error

	  //also resizes the quad
      void generateTexture();

      bool displayTextureFace;

      bool HasValidTextureFromLastTexGeneration; //set to true when generateTexture properly updates the texture; false, otherwise


   };

} //namespace Aftr

