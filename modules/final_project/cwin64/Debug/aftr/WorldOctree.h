#pragma once

#include "WorldContainer.h"
#include "WorldList.h"
#include "Model.h"
#include <set>

namespace Aftr
{

class WO;
class MGL;
class WorldOctreeNode;
class AftrGeometryOBB;

/**
   The bounding box is always centered about the origin and 
   assume the viewer is located at the origin looking along the +x axis. The 
   +z-axis is 'up' and the +y-axis equal to the +x-axis rotated 90 degrees
   counter clockwise about the +z-axis.
   subNodes[0] is "front top left"
   subNodes[1] is "front bottom left"
   subNodes[2] is "front top right"
   subNodes[3] is "front bottom right"
   subNodes[4] is "back top left"
   subNodes[5] is "back bottom left"
   subNodes[6] is "back top right"
   subNodes[7] is "back bottom right"
   Remember that because this box is oriented via this model's display matrix,
   the box could be flipped around and/or upside down, so verts[0] may not appear
   to be the "front top left" anymore.
*/
class WorldOctree : public WorldContainer
{
public:
   friend class WorldOctreeNode;

   WorldOctree( const Vector& lxlylz, Vector centerPos = Vector(0,0,0), 
                unsigned int maxDepth = 8, unsigned int maxNumModelMeshesPerNode = 10 );

   virtual ~WorldOctree();

   /**
      This method uses the Octree to logarithmically search the world volume for all
      octants that overlap with the current viewing frustum. Each mesh within these
      octants may possibly be visible. The model owning each of these meshes flags
      only the potentially visible meshes as visible; then the model is
      inserted into this instance's std::set< Model* > visibleModels.

      When rendering occurs, only the list of Models containing potentially visible
      meshes invoke Model::render( const Camera& cam ); furthermore, that Model::render( const Camera& cam ) method will
      invoke mesh::render( const Camera& cam ) only on the meshes that are potentially visible. Therefore,
      if a model has many meshes spread across the world, only the meshes within the
      frustum are sent through the graphics pipeline. Only potentially visible meshes
      and their corresponding models are touched; all other models and meshes are
      never traversed.

      This method will also reposition all meshes that have moved since the last update,
      grow the octree if necessary, and remove/shrink the depth of the octree if the
      number of meshes in a given node fall below the specified threshold.
   */
   virtual void update( const Camera& cam );

   virtual std::string toString();
   virtual std::string toStringRec();
   virtual void push_back( WO* wo );

   /*
      1) Insert to ModelMesh into the smallest octnode possible. Large Meshes may only fit in root.
      2) The octree needs to know which ModelMeshes have moved since the last update.
      The octree doesn't need an actual camera passed in to renderWorld as the update( Camera* cam )
      uses the necessary information. Other lists, however, may need a camera (such as the WorldList),
      hence the abstract base class method requires a Camera* be passed in.
   */
   virtual void renderWorld( const Camera& cam );
   virtual void renderSelf( const Camera& cam );

   WorldOctreeNode* getRootNode();
   static void computeModelMeshAABBAsMinMaxVerts( ModelMesh* m, Vector* AABBMinMax );

   unsigned int getMaxDepth() { return this->maxDepth; }
   unsigned int getMaxNumModelMeshesPerNode() { return this->maxNumModelMeshesPerNode; }


   ///toggles the bounding box of every object in the world list
   //virtual void toggleBBox();
   ///toggles the bounding box of each ModelMesh within each model
   virtual void toggleModelMeshBBox();

   virtual void onModelChangeInPosition( Model* m );
   virtual void onModelChangeInOrientation( Model* m );
   virtual void onChildWOInsertedInATopLevelWO( WO* newlyInsertedchild, WO* topLevelWO );
   virtual void onWORemovedFromContainer( WO* wo );

   /**
      When an octnode that contains no meshes and has no subdivisions is 
      too small (not enough volume) to insert a mesh, it calls this method
      and passes in a pointer to the parent of itself. Octnodes
      can only be removed 8 at a time; hence, a leaf octnode that is empty
      passes a pointer to its parent octnode. The parent octnode is then
      analyzed during WorldOctree::update() for possible removal.

      This method generates a set of octnodes that are potentially unused.
      When WorldOctree::update() is called, this set is traversed. Octnodes
      that are indeed unused, are deleted from the octree; otherwise, they
      are left alone.
   */
   void flagOctantAsPotentiallyUnused( WorldOctreeNode* node );

   /**
      Grows the octree by doubling its current dimensions.
   */
   void growOctree();
   void flagOctreeToGrow();
   ///**
   //   Grows the octree to lxlylz; if any component is smaller
   //   than the current size, that component is dismissed and the
   //   current dimension remains constant.
   //*/
   //void growOctree( const Vector& lxlylz );

   void printVisibleModelsComputedForThisFrame();
   void printSortedModelOrderForThisFrame();


protected:

   /**
      The meshes of all children WO's must also reside in the Octree of meshes;
      therefore, all root WO* that are passed in via push_back(...) must recurse
      into their children so their corresponding child WO meshes can be inserted
      into the octree as well.

      This insert does NOT push the WO* into the WorldContainer::woList. Thus
      WorldContainer::woList still container pointers only to top level WOs.
   */
   void push_backRec( WO* wo );

   /**
      Called when a Mesh moved from one OctreeNode to another. This can happen when the
      meshes changes its position/orientation, or when the current Node containing the
      Mesh is subdivided into subnodes.
      The CurrentContainingNode is passed in to further accelerate the logarithmic 
      search for the new best node container. If NULL is passed as the currentContainingNode,
      then ModelMesh* m begins its insertion from the root node and travereses down the tree
      until it finds the lowest possible node. If the currentContainingNode is passed in,
      insertion begins at that node; if the mesh is too large, the insertion process will
      try to insert in the parent node. Otherwise, the mesh will be inserted into the
      currentNode or one of its children.
      Meshes are always inserted as low in the tree as possible while still fully residing
      within one node.
   */
   int reInsertIntoOctree( ModelMesh* m, WorldOctreeNode* currentContainingNode );

   /**
      Traverses nodes within the WorldOctree::nodesContainingMeshesThatHaveMovedSinceLastUpdate
      set and re-inserts any meshes that have changed position or orientation since the last
      call to WorldOctree::update().
   */
   void updateMeshesThatHaveMovedSinceLastUpdate();

   /**
      Traverses the list generated within WorldOctree::flagOctantAsPotentiallyUnused(...)
      and invokes WorldOctreeNode::pruneNode(...), which recursively unsplits subnodes
      if the mesh count has fallen below the threshold.
   */
   void removeUnusedOctnodes();

   unsigned int maxDepth;
   unsigned int maxNumModelMeshesPerNode;

   WorldOctreeNode* root; ///< Root node of the octree

   /**
      Models that are potentially visible within the frustum this frame. This is cleared
      every frame and repopulated within WorldOctree::update(...).
   */
   std::set< Model* > visibleModels;
   
   /**
      This list is the union of visible models and the flatMGLList. All Models are sorted for
      transparency purposes and ready to be rendered from within WorldOctree:renderWorld().

      This list is cleared every frame and populated from within WorldOctree::update(). This list
      is used by WorldOctree:renderWorld() to actually render this frame to the display.
   */
   std::vector< Model* > sortedVisibleModels;

   bool GrowOctree; ///< set to true via flagOctreeToGrow(); causes growOctree() invokation during next update
   bool PrintVisibleModelsComputedForThisFrame;
   bool PrintSortedModelOrderForThisFrame;

   struct unusedOctnodeCompare
   { bool operator()( WorldOctreeNode* lhs, WorldOctreeNode* rhs ) const; };
   std::set< WorldOctreeNode*, unusedOctnodeCompare > potentiallyUnusedOctnodes;

   void sortModelsForTransparency( const Camera& cam );

   /**
      When a Model moves, callbacks on the WorldContainer are invoked informing the WorldOctree
      that a Model has moved. These callbacks trigger the octnode which contains any mesh belonging to
      that model to be inserted into this list. When WorldOctree::update() is called, each octnode
      in the list updates the corresponding mesh. This way only nodes that contain moving meshes
      are touched via the update; all other nodes are not touched.
   */
   std::set< WorldOctreeNode* > nodesContainingMeshesThatHaveMovedSinceLastUpdate;

   /**
      Models that have a NULL Model::modelDataShared pointer are placed in this list.
      These models do not have ModelMesh objects and therefore cannot be placed in
      the octree. These items do not benefit from octree acceleration. These are
      most likely all custom made MGL models since as a base instance of Model would
      most likely have a valid Model::modelDataShared pointer.
   */
   WorldList flatMGLList;
};

class WorldOctreeNode
{
public:
   WorldOctreeNode( const Vector& center, const Vector& lxlylz, unsigned int currentDepth,
                    WorldOctreeNode* parentNode, WorldOctree* worldContainerOctree );

   virtual ~WorldOctreeNode();

   unsigned int getNumNodes();
   unsigned int getNumContainedMeshes();
   void getContainedMeshes( std::set< ModelMesh* >& meshes );   
   
   WorldOctreeNode* getOctnodeAtPoint( const Vector& pt );

   void findVisibleMeshesAndFlagInParentModel( const Camera& cam, std::set< Model* >& visibleModels );

   /**
      Recursively toggles visibility of each Mesh's bounding box contained within the Octree.
   */
   void toggleMeshBBox();

   /**
      \return A string containing only information about this node, including its contained meshes.
   */
   std::string toString();
   
   /**
      \return A string containg information about this node as well as all decendents (recursive).
   */
   std::string toStringRec();

   /**
      WorldOctree contains a set of nodes that contain meshes which have moved since the last
      render. If this method is invoked, it is because this node was contained in that set.
      This method traverses this node's std::set< ModelMesh* > meshesThatHaveMovedSinceLastUpdate
      and reinserts only those nodes back into the octree thereby updating their position within
      the proper node. This node's std::set< ModelMesh* > meshesThatHaveMovedSinceLastUpdate
      is cleared after all contained meshes have been reinserted.

      This method is called by WorldOctree::update(...).
   */
   void updateContainedMeshesThatHaveMoved();

   /**
      Called by WorldOctree::onModelChangeInPosition/Orientation(...). This is called because
      a mesh contained within this node has moved. This method inserts the mesh into the
      std::set< ModelMesh* > meshesThatHaveMovedSinceLastUpdate. This set is then traversed
      from within WorldOctree::updateContainedMeshesThatHaveMoved(...).
   */
   void flagMeshForReinsertionDueToMotion( ModelMesh* m );

   /*
      Insert ModelMesh into the smallest octnode possible. Large WOs may only fit in root.
      minMaxAABB is a Vector array with 2 elements. minMaxAABB[0] is the minimum vertex
      of the current Axis Aligned Bounding Box. minMaxAABB[1] is the maximum vertex of
      the current Axis Aligned Bounding Box. These two vectors are compared against the
      axis aligned extents of the current node.
      \return the depth at which the ModelMesh was inserted; -1 if insertion failed.
   */
   int insert( ModelMesh* m, Vector* minMaxAABB );

   /**
      Recursively searches this node and all children for the in passed mesh.
      As soon as the in passed mesh is found, it is removed, and no further 
      recursion is performed.
   */
   bool removeMeshRec( ModelMesh* m );

   /**
      minMaxAABB is a Vector array with 2 elements. minMaxAABB[0] is the minimum vertex
      of the current Axis Aligned Bounding Box. minMaxAABB[1] is the maximum vertex of
      the current Axis Aligned Bounding Box. These two vectors are compared against the
      axis aligned extents of the current node.
      \return true iff ModelMesh* m fully resides within the extents of the current
      node.
   */
   bool residesFullyInNode( Vector* minMaxAABB );

   void render( const Camera& cam );

   Vector getPosition();
   Vector getLxLyLz();
   unsigned int getDepth();

   void pruneNode();

protected:

   ///Create all 8 children of this node
   void createSubNodes( unsigned int maxDepth, unsigned int maxNumWOsPerSubnode );
   //void findVisibleMeshesAndFlagInParentModelRec( const AftrGeometryOBB& frustum, std::set< Model* >& visibleModels );
   void findVisibleMeshesAndFlagInParentModelRec( const AftrGeometryFrustum& frustum, std::set< Model* >& visibleModels );

   std::vector< WorldOctreeNode* > subNodes; ///< if isLeafNode is false, this stores subNodes
   WorldOctreeNode* parentNode; ///< Pointer to this node's parent node; NULL if this is root node. Not owned by this instance
   WorldOctree* octreeContainer; ///< Pointer to the WorldContainer subclassed as the WorldOctree. Not owned by this instance

   std::set< ModelMesh* > containedMeshes;

   /**
      Populated by WorldOctree::onModelChangeInPosition/Orientation(...). These ModelMeshes have
      changed their position/orientation since the last time this node's update has been invoked.

   */
   std::set< ModelMesh* > meshesThatHaveMovedSinceLastUpdate;
   
   Vector pos; ///< center location in 3 space (x,y,z) of this octnode
   Vector dim; ///< dimensions of this octnode
   unsigned int depth; ///< Subdivison level of this octnode. Level 0 is root, 8^1 level ones, 8^2 level twos, etc

   //Rendering related methods/data
   void generateRenderInfo();
   static const GLubyte glVertIndxSize = 24;
   static const GLubyte glVertLstSize = 24;
   GLubyte* glVertIndx; ///< Indicies into the vertLst
   VertexListEntryGL_C4UB_V3F* glVertLst; ///< List of unique verticies used by this node
};

} // namespace Aftr

