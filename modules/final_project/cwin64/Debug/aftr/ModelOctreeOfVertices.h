#pragma once

#include <vector>
#include <set>
#include <map>
#include "Vector.h"
#include "AftrGeometryTriangleIndexed.h"
#include "AftrUtilities.h"

namespace Aftr
{

struct VertexListEntryGL_C4UB_V3F;
class AftrGeometryRayVsFace;

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
class ModelOctreeOfVertices
{
public:
   ModelOctreeOfVertices( const Vector& center, const Vector& lxlylz, 
                          const std::vector< Vector >& verts, 
                          const std::vector< unsigned int >& indicies,
                          unsigned int maxNumFacesPerSubnode = 100, 
                          unsigned int numSubdivisions = 4 );
   virtual ~ModelOctreeOfVertices();

   unsigned int getNumLeafNodes();
   unsigned int getNumLeafNodesContainingFaces();
   float getAvgNumOfFacesPerNode();
   unsigned int getNumContainedFaces();

   AftrGeometricTerm getNearestPointWhereLineIntersectsNearestFaceInOctee( const Vector& rayTail, 
                                    const Vector& rayHead, Vector &output, bool isLineSegment,
                                    AftrGeometryRayVsFace* hitFace = NULL,
                                    Vector* statistics = NULL );

   void getOctnodesIntersectedByLine( const Vector& rayTail, const Vector& rayHead, 
               std::map< float, ModelOctreeOfVertices* >& octnodes, bool isLineSegment );
   
   ModelOctreeOfVertices* getOctnodeAtPoint( const Vector& pt );

   std::string toString();

   void render( const Camera& cam, const Mat4& modelMat );

   /**
      \return The Index into the Model:compositeVertexList corresponding to the
      vertex which is closest to the in passed vertex p.
   */
   //std::pair< int, float > findNearestPointInThisPointSet( const Vector& p );

protected:

   ModelOctreeOfVertices( const Vector& center, const Vector& lxlylz,
                          const std::vector< Vector >& verts, const std::vector< unsigned int >& indicies,
                          unsigned int currentLevel, unsigned int maxLevel, 
                          unsigned int maxNumFacesPerSubnode );

   void createSubNodes( unsigned int maxLevel, unsigned int maxNumFacesPerSubnode, 
                        const std::vector< Vector >& verts, 
                        std::vector< unsigned int >& indicies );
   void populateLeafData( const std::vector< Vector >& verts, const std::vector< unsigned int >& indicies );
   void populateContainedVertexData( const std::vector< Vector >& verts, const std::vector< unsigned int >& indicies );
   void populateContainedFacesData(  const std::vector< Vector >& verts, const std::vector< unsigned int >& indicies );

   float computeDistanceSquaredBetween2Points( const Vector& a, const Vector& b );
   float findNearestCornerInThisSubNode( const Vector& p );

   std::string toStringRec();

   std::pair< int, float > recFindNearestPointInThisPointSet( const Vector& p, float dist );

   bool isLeafNode; ///< if true, this node contains data; otherwise, this node contains pointers to subnodes
   unsigned int level; ///< Subdivison level of this octnode. Level 0 is root, 8^1 level ones, 8^2 level twos, etc
   std::vector< ModelOctreeOfVertices* > subNodes; ///< if isLeafNode is false, this stores subNodes
   std::set< int > vertIndicies; ///< if isLeafNode is true, this stores leaf node's data (indicies into its vertList)
   
   /** if isLeafNode is true, this stores the all the faces partially or fully contained within this leaf node. */
   std::vector< AftrGeometryTriangleIndexed > containedFaces;
   
   const std::vector< Vector >& vertList; ///< Reference to the Model's compositeVertexList (do not modify this from this class, use as read only), set in constructor's initializer list
   Vector pos; ///< center location in 3 space (x,y,z) of this octnode
   Vector dim; ///< dimensions of this octnode

   //Rendering related methods/data
   void generateRenderInfo();
   static const GLubyte glIndexCount = 24;
   static const GLubyte glVertCount = 24;
   GLubyte* glIndices; ///< Indicies into the vertLst
   VertexListEntryGL_C4UB_V3F* glVerts; ///< List of unique verticies used by this node
   GLuint vao = 0;
   GLuint vertBO = 0; //Vertex Buffer Object to store vertex data
   GLuint idxBO = 0; //Index Buffer Object to store indices
};

} //namespace Aftr

