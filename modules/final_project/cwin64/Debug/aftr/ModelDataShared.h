#pragma once

#include <vector>
#include "Vector.h"
#include "ModelDataSharedID.h"
#include "BoundingBox.h"
#include "AftrBimap.h"
#include "Mat4Fwd.h"

namespace Aftr
{

class ModelMesh;

/**
   Data that defines a Model is divided into two parts - 1) per instance data and 2)
   shared data. Per instance data represents data that is specific to each instance
   of a model; this data does not make sense to share between two models. For example,
   the position and orientation of two models should be independent of each other -
   manipulating one should not manipulate the other. Furthermore, material 
   properties, textures, and shaders should not be forced to be shared amongst 
   several instances of the same model.

   However, a large part of the data makes sense to share with all instances of
   a given model. For example, the geometry/topology that defines the model should
   be placed in memory only once and shared. The same goes for Textures and shaders.

   Instances of this class are maintained by the ManagerModelMultiplicity. This
   class encapsulates data that is shared and/or duplicated across multiple instances
   of the same model. This class contains a set of meshes that define this model. Each
   mesh is composed of a skin and rendering data. This class also contains pointers to
   a composite list of all the indicies and verticies comprising the geometry of this
   instance.
*/
class ModelDataShared
{
public:
   ModelDataShared();
   /**
      This construction creates a copy of each ModelMesh within this vector. As a result,
      this object does not take ownership of any objects contained within the in passed
      vector. The user is still responsible for destroying the data inside of the in
      passed vector.  The order of the meshes passed into this constructor is preserved,
      so any object wishing to manipulate these meshes outisde this class may maintain
      their own list of indices based on those passed into this constructor; however,
      pointers to the original meshes will not work since this object contains copies.

      This constructor is called by a parser exactly once for each type of model. This
      is where the composite vertex and index lists get new'd and populated. All
      subsequent Models utilizing this ModelDataShared object share the same composite
      vertex and index lists.
   */
   ModelDataShared( const std::vector< ModelMesh* >& meshes );
   ModelDataShared( const ModelDataShared& toCopy );
   /**
      This method is invoked by the ManagerModelMultiplicity::sendModelDataSharedServerSide( ModelDataShared* m ).
      This method is invoked after all contained Meshes of this instance have had their ModelMeshRenderData 
      generated and sent server side either as a VA or VBO or VA/VBO.
   */
   virtual void onAllContainedMeshesHaveBeenSentServerSide();
   virtual ~ModelDataShared();
   ModelDataShared& operator =( const ModelDataShared& m );
   void setModelDataSharedID( const ModelDataSharedID& id );
   virtual void render( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam );
   virtual void renderSelection( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   std::vector< ModelMesh* >& getModelMeshes() { return this->meshes; }
   BoundingBox& getBoundingBox() { return this->bBox; }   
   const std::vector< Vector >& getCompositeVertexList() { return *this->compositeVertexList; }
   const std::vector< Vector >& getCompositeVertexList() const { return *this->compositeVertexList; }
   const std::vector< unsigned int >& getCompositeIndexList() { return *this->compositeIndexList; }
   const std::vector< unsigned int >& getCompositeIndexList() const { return *this->compositeIndexList; }
   std::vector< Vector* >* getCompositeTangentList() { return this->compositeTangentList; }
   std::string getFileName() { return this->id.getFileName(); }
   Vector getInitialScaleFactor() { return this->id.getScaleFactor(); }
   AftrBimap< std::pair< size_t, size_t >, std::pair< size_t, size_t > >& getIndexAlias() { return indexAlias; }

   /**
      Called by ManagerModelMultiplicity::destroyModelSharedData(...) when all instances
      of this ModelDataShared are destroyed. Since this composite list is shared amongst all
      instances, the destructor for this class does not destroy the composite index, vertex,
      tangent, etc lists - this is the responsibility of the ManagerModelMultiplicity.
   */
   void destroyCompositeLists();

   virtual void generateCompositeGenericAttributeLists();

   /**
      Maps the compositeIndex i to the mesh index and vertex entry index within the mesh's VBO or VA.
      For example, mapCompositeIndexToSubMeshIDandIndex[ this->compositeIndexList[1] ] = (0,238).
      
      Above, the user selected the 1st index in the composite index list (hence [1]). The 
      mapCompositeIndexToSubMeshIDandIndex then returns a tuple denoting which meshIdx and vertex Entry
      index corresponds to that index. In this example, ModelDataShared::mesh[0] at VBO / VA index 238
      corresponds to the 1st index in the compositeIndexList.
   */
   std::map< unsigned int, std::pair< unsigned int, unsigned int > >& getMapCompositeIndexToSubMeshIndex() { return this->mapCompositeIndexToSubMeshIDandIndex; }

protected:

   virtual void generateCompositeTangentList();
   virtual void generateCompositeQuadricList();

   void initMemberData();

   /**
      Unique identifier used by ManagerModelMultiplicity. This is managed (created and
      destroyed) by the ManagerModelMultiplicity, the user should not modify this object.
   */
   ModelDataSharedID id;

   BoundingBox bBox; ///< The cumulative bounding box for this ModelDataShared

   /**
      A collection of all the submeshes that define this model's appearance. Each ModelMesh
      contains a ModelMeshSkin (controls textures/mutli-textures/shaders/material properties/
      flat or smooth shading) and a ModelMeshDataShared (contains all relevant OpenGL data
      used to render the submesh to the display (efficient handling of VBOs/VAs based on
      machine-specific supported hardware)).

      This vector is owned by this specific instance. The destructors for the ModelMesh,
      however, do not destroy the shared data (such as the OpenGL VBO/VA geometry) only
      instance-specific data is destroyed (such as the Skin properties).
   */
   std::vector< ModelMesh* > meshes;

   /**
      A collection of all the unique vertices contained across all submeshes defining this
      model. This data is stored once in memory and managed via the ManagerModelMultiplicity.
      This data is used by the physics engine as well as Aftr utilities such as the 
      ray-casting functions / octree optimizations, etc. Normally, the user does not need to
      modify this list. This list is populated once on construction, changing this list does
      not affect the OpenGL geometry that is rendered nor will it affect the Physics Engine's
      collision detection if the Physics Engine has already been instantiated. For a model
      loaded from file (.wrl, .3ds, .lwo, etc...) This list is a copy of the vertex data
      originally parsed and stored in the ModelMeshRenderDataGenerator class.
      populated by the parser.
   */
   std::vector< Vector >* compositeVertexList = nullptr; // perhaps should become std::shared_ptr<>

   /**
      The set of indicies into this this object's compositeVertexList.
   */
   std::vector< unsigned int >* compositeIndexList = nullptr; // perhaps should become std::shared_ptr<>

   /**
      Maps the compositeIndex i to the mesh index and vertex entry index within the mesh's VBO or VA.
      For example, mapCompositeIndexToSubMeshIDandIndex[ this->compositeIndexList[1] ] = (0,238).
      
      Above, the user selected the 1st index in the composite index list (hence [1]). The 
      mapCompositeIndexToSubMeshIDandIndex then returns a tuple denoting which meshIdx and vertex Entry
      index corresponds to that index. In this example, ModelDataShared::mesh[0] at VBO / VA index 238
      corresponds to the 1st index in the compositeIndexList.
   */
   std::map< unsigned int, std::pair< unsigned int, unsigned int > > mapCompositeIndexToSubMeshIDandIndex;
   
   /**
      A collection of each vertices's corresponding tangent vector (tangent attribute) if
      tangents were generated during construction.
   */
   std::vector< Vector* >* compositeTangentList = nullptr;

   /**
      Stores a bidirectional mapping between the original pair of 
      mesh index / vertex index onto the  current 
      mesh index / vertex index corresponding to the current
      location of that vertex. The original pair are those which are
      passed into the constructor for this ModelDataShared instance.

      For example, if Vertex v was originally in this->meshes.at( 0 ) at 
      index 13, but was then reloacted for some reason, 
      such as a mesh splitting process (for frustum acceleration), 
      to this->meshes.at( 28 ) at index 456
      bidirectional map would contain:
      ( 0, 13 ) <--> ( 28, 456 )

      If this map's size is greater than zero, it implies the original
      verticies have been reorganized. The left hand side (lhs) of the bimap
      contains one entry for each original position of a given vertex; 
      the right hand side (rhs) of the bimap contains one entry for 
      the current position of a given vertex.  When manipulating VA/VBO 
      data, ensure the current position is being used, not the original.
   */
   AftrBimap< std::pair< size_t, size_t >, std::pair< size_t, size_t > > indexAlias;
};

} //namespace Aftr

