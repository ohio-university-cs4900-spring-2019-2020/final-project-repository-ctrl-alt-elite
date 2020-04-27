#pragma once

#include <vector>
#include <set>
#include <map>
#include "AftrOpenGLIncludes.h"
#include "Vector.h"

namespace Aftr
{
class ModelMesh;
class ExtrusionWeights;
class StripTree;   enum topologyRenderType {//strongly typed enumerator support was tested, but standard syntax "enum class" didn't compile, note: forward declared enums are supported in c++ 0x
      trtTOPOLOGY = 1 << 0,//draws lines between each mesh
      trtBORDER = 1 << 1,//draws a border around the AABB of the mesh
      trtCONNECTIVE = 1 << 2,
      trtBASEAABB = 1 << 3,
      trtBASETBB = 1 << 4,
      trtTEXTURE_BASEAABB = 1 << 5,
      trtTEXTURE_BASETBB = 1 << 6,
      trtTEXTURE_BASE_METHOD1 = 1 << 7,
      trtTEXTURE_CONNECTIVE_METHOD1 = 1 << 8, //connective method 1 uses equal amounts for main polygon and connective (.5, .5)
      //connective method 2 uses an amount based on the lengths in the orthonormal basis directions
      //connetive method 3 uses an amount based on the on screen areas using math
      //connective method 4 uses an amount based on the on screen areas using occlusion queries
      trtINTERFACES = 1 << 9
   };

   enum connectivityRendertype
   {
      crtLINES = 1 << 0,
      crtQUADS = 1 << 1,
      crtTEXTURED = 1 << 2,
      crtTEXTURED_CHAIN = 1 << 3
   };

   enum connectivityTexturedTypes
   {
      cttTHIRDS = 1 << 0,
      cttSSSize = 1 << 1,
      cttCORRECT = 1 << 2
   };

   enum connectivityColoringType
   {
      cctCOLORED = 1 << 0,
      cctTEXTURED = 1 << 1
   };


   struct GridNode
   {
      int self;
      int north;
      int east;
      int south;
      int west;
   };

   class GridTopology
   {
   public:
      GridTopology();
      void setSize( int x, int y );
      void render( const Camera& cam );
      void setMeshes( std::vector< ModelMesh* >& meshes  );
      void setSkipped(  std::vector< size_t >& skipped );
      void update();
      std::vector< ModelMesh* > getMeshes() { return meshes; } 
      std::vector< std::vector< GridNode > > getGraph() { return graph; }
      int renderType;//bitmask of which component to render
      int connectivityType;//bitmeask of how to render connectivity
      int connectivityTexturedType;//bitmask of what extrusion weights to use for the textured connectivity quads
      int connectivityColoringType;//bitmask of whether connectivity should be colored or textured

        //reports
      void getDisplacementReport();
      std::string toStringExtrusionWeights();
      virtual ~GridTopology();
      void setStripTreeRenderLevel( int meshX, int meshY, int renderLevel );

      void updatePolicy( const std::vector< ModelMesh* >& meshes );

      int maxStripLevel;
      void processMeshes();//allows the update of strip tree levels

      bool renderMain;
      bool renderFrontBack;
      bool renderLeftRight;

   protected:
      std::vector< std::vector< GridNode > > graph;
      std::vector< ModelMesh* > meshes;
      std::vector< size_t > skipped; 
      /*
      enum topologyRenderType { 
      trtTOPOLOGY = 1 << 0,//draws lines between each mesh
      trtBORDER = 1 << 1,//draws a border around the AABB of the mesh
      trtCONNECTIVE = 1 << 2,
      trtBASEAABB = 1 << 3,
      trtBASETBB = 1 << 4,
      trtTEXTURE_BASEABB = 1 << 5,
      trtTEXTURE_BASETBB = 1 << 6,
      trtTEXTURE_BASE_METHOD1 = 1 << 7,
      trtTEXTURE_CONNECTIVE_METHOD1 = 1 << 8 };
      */
      //render methods for each render type
      void renderTopology();
      void renderBorders();
      void renderConnectivity();
      void renderBaseAABB();
      void renderBaseTBB();
      void renderTextureBaseAABB();
      void renderTextureBaseTBB();
      void renderTextureBaseMethod1();
      void renderConnectivityMethod1();
      void renderInterfaces();

      //connectivity render methods
      void renderConnectivityLines(int i, int j);
      void renderConnectivityQuads(int i, int j);
      void renderConnectivityTextured(int i, int j);//uses fixed edge
      void renderConnectivityTexturedChain( int i, int j );//uses strip tree
      void renderConnectivityTexturedChain2( int i, int j );//uses strip tree

      void renderAuxilleryQuads(int i, int j);
      void renderAuxilleryQuadsCase1( int i, int j, int foundVertex );
      void renderAuxilleryQuadsCase2( int i, int j, GLfloat** vertices );
      void renderAuxilleryChain( int i, int j );
      void renderAuxilleryChainCase1( int i, int j );
      void renderAuxilleryChainCase2( int i, int j );
      void renderAuxilleryChainCase3( int i, int j );

     // ExtrusionWeights* extrusionWeights;
      
      double distanceThreshold;
      
      
      //The strip tree is the merged interface from the left and right of a pair of meshes
      //during creation points are pulled from 2 meshes (if they exist)
      //then the tree is generated 
      std::vector< std::vector< StripTree* > > leftXEdgeStripTrees;
      std::vector< std::vector< StripTree* > > rightXEdgeStripTrees;
      std::vector< std::vector< StripTree* > > frontYEdgeStripTrees;
      std::vector< std::vector< StripTree* > > backYEdgeStripTrees;

      //std::vector< std::vector< StripTree* > > mergedFrontBackYEdgeStripTrees;//not used for our tests

      //a flat list, indices correspond to meshes gt (this come out of the transformation and aren't pointers)
      std::vector< std::vector< VectorD > > leftXEdgeChainProjectedIntoPlaneInWorldSpace;
      std::vector< std::vector< Vector > > leftXEdgeChainTexCoords;
      std::vector< std::vector< VectorD > > rightXEdgeChainProjectedIntoPlaneInWorldSpace;
      std::vector< std::vector< Vector > > rightXEdgeChainTexCoords;
       std::vector< std::vector< VectorD > > frontYEdgeChainProjectedIntoPlaneInWorldSpace;
      std::vector< std::vector< Vector > > frontYEdgeChainTexCoords;
      std::vector< std::vector< VectorD > > backYEdgeChainProjectedIntoPlaneInWorldSpace;
      std::vector< std::vector< Vector > > backYEdgeChainTexCoords;

      //the points that go in each interface (pointers to existing vertices in the meshes)
      std::vector< std::vector< std::vector< Vector* > > > leftXEdgePoints;
      std::vector< std::vector< std::vector< Vector* > > > rightXEdgePoints;
      std::vector< std::vector< std::vector< Vector* > > > frontYEdgePoints;
      std::vector< std::vector< std::vector< Vector* > > > backYEdgePoints;
      std::vector< std::vector< int > > stripTreeRenderLevels;

      std::vector< Vector* > extraPoints;//extra exterme points inserted not owned by the model mesh that will need cleaned up later

      void transformChain( StripTree* tree, double newZ, std::vector< Vector >& texCoords, std::vector< VectorD >& coords, const VectorD& offset, ModelMesh* mesh );     
    

   };

}

