#pragma once

#include "AftrOpenGLIncludes.h"
#include "AftrGlobals.h"
#include "ModelMeshSkin.h"
#include "BoundingBox.h"
#include "AftrGeometryOBB.h"
#include "Vector.h"
#include "Mat4Fwd.h"
#include <vector>

namespace Aftr
{

class ModelMeshDataShared;
class WorldOctreeNode;
class Camera;
class ModelMeshLOD;

/**
   This class encapsulates a skin and rendering information specific to one mesh.
   The ModelMeshDataShared object is a pointer to the shared geometry information
   used by all identical meshes. The skin, however, is a copy of the original 
   skin loaded from file. The user can easily manipulate the skin to change the
   texture, shader, material properties, etc so this rendered mesh looks much
   different from the original even though it is using the originals geometry.

   After creating the ModelMesh, the user should manually invoke 
   ModelMesh::setParentModel( Model* parent ); so this mesh can access the
   parent Model's position/orientation/hierarchy information. This information
   is used by the culling system as well as methods such as getCurrentPosition(),
   etc.
*/
class ModelMesh
{
public:
   ModelMesh();
   ModelMesh( const ModelMeshSkin& skin, ModelMeshDataShared* meshData );
   ModelMesh( const ModelMesh& toCopy );
   virtual ~ModelMesh();
   ModelMesh& operator =( const ModelMesh& m );
   ModelMeshDataShared* getMeshDataShared();
   ModelMeshSkin& getSkin();
   std::vector< ModelMeshSkin >& getSkins();
   void addSkin( const ModelMeshSkin& skin );
   void useNextSkin();
   void usePreviousSkin();
   void useSkinAtIndex( size_t skinIndex );
   size_t getSkinIndex() { return this->skinIndex; }
   BoundingBox& getBoundingBox() { return this->bBox; }
   bool renderBBox;
   virtual void render( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam );
   virtual void renderSelection( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   void setParentModel( Model* parentModel );
   Model* getParentModel() const;
   WorldOctreeNode* getWorldOctreeNodeContainingThisMesh();
   void setWorldOctreeNodeContainingThisMesh( WorldOctreeNode* node );

   const std::string& getDescription() { return this->description; }
   void setDescription( const std::string& description ) { this->description = description; }
   
   /**
      Returns the current global x,y,z of the center of this Mesh.
      Prereq: The Mesh's parent model must be set via ModelMesh::setParentModel().
   */
   Vector getCurrentPositionGlobal() const;

   /**
      Returns the current offset between this Mesh's center point and the
      parent model's center point.
      Prereq: The Mesh's parent model must be set via ModelMesh::setParentModel().
   */
   Vector getCurrentOffsetFromParentModel();
   
   /**
      Returns the original offset between this Mesh's center point and the
      Parent Model's center point. That is, this vector is the Mesh's center point
      minus the Parent Model's center point when the Parent Model's center point
      is at the origin with an identity orientation. Since each Mesh's orientation
      is defined by the Parent Model's orientation, a meshes current position is
      always equal to this offset vector transformed by the parent model's display
      matrix plus the parent model's current position.

      Prereq: The Mesh's parent model must be set via ModelMesh::setParentModel().
   */
   Vector getOriginalOffsetFromParentModel();

   /**
      This method sets this Mesh's offset from the center of the parent model. This method
      is typically only used when the mesh of a model has to be moved independently of the model.
      After this method has been invoked, the new global position of this mesh will take the
      parent model's position/orientation into account as well as this original vector transformed
      by the parent model's display matrix.
   */
   void setOriginalOffsetFromParentModel( const Vector& offset );

   /**
      Returns the current Oriented Bounding Box located at the mesh's current
      position and oriented with the mesh's current orientation.
   */
   AftrGeometryOBB getCurrentOBB() const;

   /**
      Using the position and orientation of the in passed cam, this method computes
      the screen space coordinate of this mesh's center point. The screen space (Window space)
      x, y values are placed in outWindowSpace. outWindowSpace.z is the depth into the screen
      at which the mesh's center point resides. outPerspectiveDivide is the w component used
      during the homogeneous transformation. This value is useful if one wants to transform 
      from screen space back into world space without relying a 16/24 bit depth buffer which
      introduces round off error.
   */
   void getScreenSpaceCoordinateOfCurrentPosition( Camera* cam, Vector& outWindowSpace, float& outPerspectiveDivideScalar );

   /**
      Given this mesh's current global position / orientation and the in passed 
      camera's current position / viewing properties, this method computes the
      lengths of a billboarded quad in world space. This billboarded quad is the proper 
      size for rending this mesh to an texture (from camera) and binding that 
      texture across the quad. The returned X is the billboards width, and the
      returned Y is the billboards height.

      This method is utilized by the LOD system.

      Returns the Lx and Ly lengths of the billboard's geometry when rendered
      from camera at this mesh's current global position. Lx and Ly are stored in
      the returned vector's .x and .y components, respectively. Lx and Ly are
      in world space.
   */
   Vector getBillboardLxLyInWorldSpace( Camera* cam, Vector* outBillboardCenterPosInWorldSpace = nullptr ) const;
   Vector getBillboardLxLyInWorldSpaceCachingIntermediateState( Camera* cam, Vector* outBillboardCenterPosInWorldSpace, Vector* outBillboardCenterPosInWorldSpaceUnpacked );

   /**
      This method takes the current 8 vertices of the this mesh's current
      OBB, transforms them from world space to screen space, builds a tight axis-aligned 
      bounding box, and transforms these new 4 screen space verts back to world space.
      Then the x and y lengths are computed and returned. No z values are returned as
      x represents the billboard's width and y represents the billboard's height.

      Optionally, if the user would also like to retrive the w (perspective divide scalar) of
      this mesh's current centerposition (in world space), an out only point may be passed in.
   */
   Vector getBillboardLxLyInScreenSpace( Camera* cam, Vector* outMeshCenterPtInScreenSpace = nullptr, 
                                         float* outMeshCenterPtPerspectiveDivideScalar = nullptr,
                                         Vector* outCenterOfSSBBox = nullptr ) const;
   Vector getBillboardLxLyInScreenSpaceCachingIntermediateState( Camera* cam,
                                         Vector* outMeshCenterPtInScreenSpace = nullptr, Vector* outMeshCenterPtInScreenSpaceUnpacked = nullptr,
                                         float* outMeshCenterPtPerspectiveDivideScalar = nullptr,
                                         Vector* outCenterOfSSBBox = nullptr , Vector* outCenterOfSSBoxUnpacked = nullptr );


   /**
      Adds the LOD representation specified by 'lod' into this Mesh's collection of available
      LODs. Returns the index into this Mesh's LOD list where the newly added LOD is stored.
      This index is used as input when invoking ModelMesh::setCurrentLOD().
      To actually use the LOD during rendering, the user must invoke 
      ModelMesh::startUsingCurrentLOD(). To stop using the current LOD, the user must invoke
      ModelMesh::stopUsingCurrentLOD().
   */
   size_t addLOD( ModelMeshLOD* lod );

   /**
      Returns true, if the in passed index is valid and this Mesh's current LOD is set to that
      index; false, otherwise.
   */
   bool setCurrentLODIndex( size_t index );

   /**
      Returns the index of the currently used LOD. In order for the LOD to affect rendering of
      this mesh, ModelMesh::startUsingCurrentLOD() must have been invoked. In order to stop the
      LOD rendering, call ModelMesh::stopUsingCurrentLOD()
   */
   size_t getCurrentLODIndex() const { return this->currentLODIndex; }

   bool isUsingCurrentLOD() const { return this->useLODAtRender; }
   bool isUsingCurrentLOD( bool startUsingLODAtMeshRender );

   /**
      Returns the currently used LOD, as determined by the currently set LOD index 
      (ModelMesh::setCurrentLOD( idx )).
   */
   ModelMeshLOD* getCurrentLOD() const;

   /**
      Returns a reference to a std::vector containing all current ModelMeshLODs representing
      this mesh. Each LOD represents one specific LOD algorithm / representation; hence, there
      will typically be one or few entries in this vector.
   */
   std::vector< ModelMeshLOD* >& getLODs() { return this->lods; }

    std::vector< VectorD >  findTightSSPoints( const std::vector< VectorD >& obbVertsSS, std::vector< int >& indices ) ;

   std::vector< VectorD > getCachedWSTightVertices() { return this->cachedWSTightPointsDoublePrecision; }
   std::vector< VectorD > getCachedTightTextureCoordinates() { return this->cachedTightTextureCoordinates; }

   Vector getCachedSSCenterPoint() { return this->cachedSSCenterPt; }

   //
   //Edge Based Getters
   //

   //Vertices (length 6)
   //X edges
   void getCachedBBWSTopLeftXEdge( GLfloat* verts );
   void getCachedBBWSBottomLeftXEdge( GLfloat* verts );
   void getCachedBBWSTopRightXEdge( GLfloat* verts );
   void getCachedBBWSBottomRightXEdge( GLfloat* verts );
   //Y edges
   void getCachedBBWSTopFrontYEdge( GLfloat* verts );
   void getCachedBBWSBottomFrontYEdge( GLfloat* verts );
   void getCachedBBWSTopBackYEdge( GLfloat* verts );
   void getCachedBBWSBottomBackYEdge( GLfloat* verts );
   //Z edges
   void getCachedBBWSFrontLeftZEdge( GLfloat* verts );
   void getCachedBBWSRearLeftZEdge( GLfloat* verts );
   void getCachedBBWSFrontRightZEdge( GLfloat* verts );
   void getCachedBBWSRearRightZEdge( GLfloat* verts );

   //Texture Coordinates (length 4)
   //X edges
   void getCachedBBWSTopLeftXEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSBottomLeftXEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSTopRightXEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSBottomRightXEdgeTextureCoordinates( GLfloat* verts );
   //Y edges
   void getCachedBBWSTopFrontYEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSBottomFrontYEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSTopBackYEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSBottomBackYEdgeTextureCoordinates( GLfloat* verts );
   //Z edges
   void getCachedBBWSFrontLeftZEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSRearLeftZEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSFrontRightZEdgeTextureCoordinates( GLfloat* verts );
   void getCachedBBWSRearRightZEdgeTextureCoordinates( GLfloat* verts );

   //Screen Spaced Coordinates (length 4)
   //X edges
   void getCachedBBSSTopLeftXEdge( GLfloat* verts );
   void getCachedBBSSBottomLeftXEdge( GLfloat* verts );
   void getCachedBBSSTopRightXEdge( GLfloat* verts );
   void getCachedBBSSBottomRightXEdge( GLfloat* verts );
   //Y edges
   void getCachedBBSSTopFrontYEdge( GLfloat* verts );
   void getCachedBBSSBottomFrontYEdge( GLfloat* verts );
   void getCachedBBSSTopBackYEdge( GLfloat* verts );
   void getCachedBBSSBottomBackYEdge( GLfloat* verts );
   //Z edges
   void getCachedBBSSFrontLeftZEdge( GLfloat* verts );
   void getCachedBBSSRearLeftZEdge( GLfloat* verts );
   void getCachedBBSSFrontRightZEdge( GLfloat* verts );
   void getCachedBBSSRearRightZEdge( GLfloat* verts );


   std::vector< VectorD > getCachedWSBBPoints() { return this->cachedFullWSBBPoints; }

   std::string printReportOfCachedTransformations();

   void recomputeOffsetFromCenterOfParentModel();

   Vector getCachedLxLySS() { return this->cachedLxLySS; }
   Vector getCachedSSCenterPt() { return this->cachedSSCenterPt; }

   /**
      Modifies the underlying model mesh's modelMeshRenderData to re-sample the vertices
      currently only works for points, re-sampling techniques should be possible for other primitive shapes
      but may not make sense for all models (undersampling triangles will leave gaps in the model).
      Currently uses the currently selected skin's prim-type, render-type pair, could be extended to modify
      a specified pairing.
      Factor is the undersampling factor relative to the ORIGINAL data (easy enough for sequential data, may
      take more thought for other types, i.e. passing in 2 will give you half as many original points,
      followed by a subsuquent call of 3 will give you one third as many points, not one sixth.
   */
   void underSampleMeshWithFactor( int factor );
protected:

   void initMemberData();
   void computeOffsetFromCenterOfParentModel();///< only called in constructor, use "recompute" if you manually change the bounding box or something equivilent later

   std::vector< ModelMeshSkin > skins;
   size_t skinIndex; ///< Current skin
   BoundingBox bBox; ///< BoundingBox of this Mesh's geometry

   std::vector< ModelMeshLOD* > lods; ///< Each entry represents one LOD algorithm representing this mesh
   size_t currentLODIndex; ///< Specifies which LOD this mesh is set to currently use.
   bool useLODAtRender; ///If true, this Mesh's render will use the currently selected LOD, instead of this Mesh's actual geometry/skins

   /**
      Vector originating at the parent model's center point (tail) and 
      extending to the center point of this mesh (head). This is initialized
      and maintained when ModelMesh::setParentModel(...) is invoked.
   */
   Vector offsetFromCenterOfParentModel;
   
   /**
      If the simulation is using the WorldOctree for rendering acceleration,
      this pointer points to the node within the octree that currently stores
      this mesh. This mesh will reside in at most one node of the octree at 
      any given time. This pointer is set and maintained by the WorldOctree
      instance accelerating the simulation's rendering. The user typically
      does not need to manipulate this. The pointed to node is not owned by
      this mesh, the mesh should not delete it.
   */
   WorldOctreeNode* octreeNodeContainingThisMesh;

   /**
      Pointer to the Model that uses this ModelMesh. This pointer is
      valid only after the parent model completely exits its Model::New()
      method; as a result, this pointer is not valid during any initialization
      of the ModelMesh. This pointer is intended to be used by acceleration
      structures during rendering. This allows those acceleration structures
      to traverse both from a WO -> Model -> ModelMesh and 
      ModelMesh -> Model -> WO during runtime (not initialization).
   */
   Model* parentModel = nullptr;

   //Shared Data
   ModelMeshDataShared* meshData = nullptr; //pointer to the original meshData; not owned by this instance, do not delete

   //Optional textual description describing this mesh.
   //Convenient for setting color/material properties on a specific mesh loaded from a file.
   std::string description = "";


   //
   //cache
   //

   //"Full" lists contain all 8 points in the standard bbox ordering
   //this is opposed to "Tight" lists which contain the convex hull ordered points
   std::vector< VectorD > cachedFullSSBBPoints;///< the most recently generated set of the BB points in screen space (and center)
   //std::vector< VectorD > cachedFullSSBBPointsUnpacked;
   std::vector< VectorD > cachedFullWSBBPoints;///< the most recently generate set of the BB points in world space
   //std::vector< VectorD > cachedFullWSBBPointsUnpacked;// should be r
   std::vector< VectorD > cachedFullTextureCoordinates;

   //"Tight" points are the sorted convex hull points of the object, usually 6 points
   //this is opposed to the "full" list which has all 8 points in the standard bbox ordering
   //std::vector< Vector > cachedSSTightPoints;///< the most recently generated set of points in screen space represented as a convex hull
   std::vector< VectorD > cachedSSTightPointsDoublePrecision;//sorted indices
   //std::vector< VectorD > cachedSSTightPointsDoublePrecisionUnpacked;//sorted indices
   std::vector< VectorD > cachedWSTightPointsDoublePrecision;//sorted indices
   //std::vector< VectorD > cachedWSTightPointsDoublePrecisionUnpacked;//sorted indices
   std::vector< VectorD > cachedTightTextureCoordinates;
   std::vector< VectorD > cachedOriginalPoints;//sorted indices
   double cachedDisplacementFromCamera;
   VectorD cachedCameraLookDir;
   //std::vector< Vector > cachedWSTightPointsProjected;
   //std::vector< Vector > cachedWSTightPointsUnprojected;
   std::vector< int > cachedWSTightPointIndices;
   std::vector< double > cachedBBPDSs;
   //std::vector< float > cachedTightPDSs;
   std::vector< double > cachedTightPDSsDoublePrecision;

   Vector cachedLxLySS;
   Vector cachedSSCenterPt;

};

}

