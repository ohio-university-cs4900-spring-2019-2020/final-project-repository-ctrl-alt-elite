#pragma once

#include "AftrOpenGLIncludes.h"
#include "AftrGlobals.h"
#include <vector>
#include <string>
#include "ModelMeshRenderDataGenerator.h"
#include "ModelMeshRenderData.h"

namespace Aftr
{

class ModelMeshSkin;



/**
   This class encapsulates all the information necessary to render the underlying
   geometry of a mesh. The associated skins (materials, textures, shaders,etc) are
   expected to already be bound before this mesh's render is invoked. This geometry
   is rendered using either flat shading (one normal per face) or smooth shading
   (one normal per vertex).

   Upon invocation of generateRenderData(...), the generated shading type is determined
   by the corresponding skin's shading type.
   If the skin's shadingType is changed later on, this method's
   generateRenderData(...) must be reinvoked passing in the new shadingType of either
   MESH_SHADING_TYPE::mstFLAT or MESH_SHADING_TYPE::mstSMOOTH.
   
   Internally, both the flat shaded data and smooth shaded data may exist concurrently
   if both shading types have been generated via generateRenderData(...). However, the
   default behavior only loads the skin's default shading type; this saves memory on
   both the graphics card and CPU-side.

   All meshes are rendered via OpenGL using indexed geometry objects; namely,
   Vertex Buffer Objects (VBOs) or Vertex Arrays (VAs). If the current
   machine supports VBOs, all non-deformable geometry is placed in a VBO and
   rendered via a Vertex Array encapsulating the constituient VBO buffers;
   this sends all data to the graphics card exactly once at load time. Any 
   rendering of these objects is then performed on graphics
   hardware limited only by the graphics hardware. If the current machine does not
   support VAs/VBOs, or if the geometry is deformable, then VAs are used to perform
   the rendering. VAs send the data to the graphics card each render; however
   optimized drivers cache the VA data on the graphics card and only need to
   update the deformed geometry. Again, all rendering is done with indexed
   geometry; that is, no display lists, no immediate mode rendering.
*/
class ModelMeshDataShared
{
public:
   ModelMeshDataShared();
   ///In passed renderDataGenerator's ownership is given to this instance.
   ModelMeshDataShared( std::unique_ptr<ModelMeshRenderDataGenerator > renderDataGenerator );

   ///This constructor consumes/takes ownership of the in passed ModelMeshRenderData* object. This is used when
   ///a generator isn't necessarily needed, but the in passed render data ought to be used as is. For example,
   ///The Asset Importer library (assimp) performs the primitive type conversion and shading operators that the 
   ///ModelMeshRenderDataGenerator usually does. If assimp already does this, we don't want to redo that work.
   ///It's also likely that assimp does this conversion more efficiently and timely than the generator class.
   ///The user must also pass in the corresponding shading type of the contained render data (smooth or flat).
   ///The user must also pass in the OpenGL Primitive type of the rendered primitives, ie GL_TRIANGLES, 
   ///GL_TRIANGLE_STRIP, GL_POINTS, etc.
   ModelMeshDataShared( ModelMeshRenderData* renderData, const MESH_SHADING_TYPE& mstType, GLenum glPrimType,
                        bool destroyCPUSideDataAfterSendingToGPU = true );

   virtual ~ModelMeshDataShared();
   /**
      This method is invoked by the ManagerModelMultiplicity and uses the data
      from the in passed ModelMeshRenderDataGenerator* renderDataGenerator to construct the Indexed Geometry
      (VBO or VA), generate all necessary OpenGL handles, send the data to graphics
      memory, and everything else necessary to make this instance's render() method
      correctly draw the model.
   */
   virtual void generateRenderData( MESH_SHADING_TYPE shadingType, MESH_RENDER_TYPE renderType = MESH_RENDER_TYPE::mrtVBO, GLenum glPrimType = GL_TRIANGLES );
   /**
      This method is called manually when the underlying ModelMeshRenderData for a specific shading/render type is already generated, but the underlying generator
      has changed size, so mapping isn't sufficient.
   */
   virtual void regenerateRenderData(MESH_SHADING_TYPE shadingType, MESH_RENDER_TYPE renderType, GLenum glPrimType);
   virtual bool hasGeneratedRenderData( MESH_SHADING_TYPE shadingType, GLenum primType );
   std::string toString() const;
   virtual void render( ModelMeshSkin& skin );
   virtual void renderSelection( const ModelMeshSkin& skin, GLubyte red, GLubyte green, GLubyte blue );

   bool isUsingVBO( MESH_SHADING_TYPE shadingType, GLenum glPrimType );
   bool isUsingVA( MESH_SHADING_TYPE shadingType, GLenum glPrimType );

   ModelMeshRenderDataGenerator* getRenderDataGenerator();
   void setRenderDataGenerator( std::unique_ptr<ModelMeshRenderDataGenerator > g );

   ModelMeshRenderData* getModelMeshRenderData( MESH_SHADING_TYPE shadingType, GLenum primType );

   ///This method simply inserts the corresponding render data and shading info into. For example,
   ///The Asset Importer library (assimp) performs the primitive type conversion and shading operators that the 
   ///ModelMeshRenderDataGenerator usually does. If assimp already does this, we don't want to redo that work.
   ///It's also likely that assimp does this conversion more efficiently and timely than the generator class.
   ///The user must also pass in the corresponding shading type of the contained render data (smooth or flat).
   ///The user must also pass in the OpenGL Primitive type of the rendered primitives, ie GL_TRIANGLES, 
   ///GL_TRIANGLE_STRIP, GL_POINTS, etc.
   ///If an existing renderData is already associated with the corresponding shadingType & glPrimType, the
   ///bool overwriteExistingMMRD is used to determine if the existing renderData will be destroyed and replaced
   ///with the in pass renderData. If overwriteExistingMMRD is true, the existing renderData will be replaced,
   ///otherwise it will not be replaced.
   ///If destroyCPUSideDataAfterSendingToGPU is true, the CPU's copy of the render data (vertex info, index info, etc) will
   ///be deleted once a GPU-side copy has been made. Deleting it is free CPU-side memory, but the CPU may lost quick
   ///access to the total set of vertices which may want to be used by the physics engine at a later time.
   //template< typename V, typename I >
   bool addModelMeshRenderData( ModelMeshRenderData* renderData,
                                const MESH_SHADING_TYPE& shadingType, GLenum glPrimType,
                                bool overwriteExistingMMRD = true, bool destroyCPUSideDataAfterSendingToGPU = true );

   //modifies the underlying model mesh's modelMeshRenderData to re-sample the vertices
   //currently only works for points, re-sampling techniques should be possible for other primitive shapes
   //but may not make sense for all models (under sampling triangles will leave gaps in the model).
   //Currently uses the currently selected skin's prim-type, render-type pair, could be extended to modify
   //a specified pairing.
   //Factor is the under sampling factor relative to the ORIGINAL data (easy enough for sequential data, may
   //take more thought for other types, i.e. passing in 2 will give you half as many original points,
   //followed by a subsequent call of 3 will give you one third as many points, not one sixth.
   void underSampleMeshWithFactor( int factor, const ModelMeshSkin& skin );

protected:

   void initMemberData( std::unique_ptr<ModelMeshRenderDataGenerator > renderDataGenerator );
   void sendDataServerSide( ModelMeshRenderData& r );

   virtual void render( ModelMeshSkin& skin, ModelMeshRenderData& r );
   virtual void renderMeshCompatibility( ModelMeshSkin& skin, const ModelMeshRenderData& r );
   virtual void renderMeshGL32( ModelMeshSkin& skin, const ModelMeshRenderData& r );
   virtual void renderNormals(  ModelMeshSkin& skin, ModelMeshRenderData& r );
   virtual void renderSelection( const ModelMeshSkin& skin, const ModelMeshRenderData& r, GLubyte red, GLubyte green, GLubyte blue );
   virtual void renderMeshSelectionCompatibility( const ModelMeshSkin& skin, const ModelMeshRenderData& r, GLubyte red, GLubyte green, GLubyte blue );
   virtual void renderMeshSelectionGL32( const ModelMeshSkin& skin, const ModelMeshRenderData& r );

   ///Map of shading type and GL Primitive Type: (GL_TRIANGLES, GL_POINTS, GL_TRIANGLE_STRIP, etc
   std::map< std::pair< MESH_SHADING_TYPE , GLenum >, ModelMeshRenderData* > renderDataMap;

   std::unique_ptr<ModelMeshRenderDataGenerator > renderDataGenerator = nullptr; ///< Mesh data populated from parser
};

}

