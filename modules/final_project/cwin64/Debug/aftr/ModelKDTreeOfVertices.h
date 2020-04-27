#pragma once

#include <vector>
#include <set>
#include <iostream>
#include "Vector.h"
#include <tuple>

namespace Aftr
{

class Model;

class ModelKDTreeOfVertices
{
protected:

   class TreeNode
   {
   public:
      TreeNode();
      virtual ~TreeNode();
      unsigned int value = -1; ///< index into Model::compositeVertexList
      TreeNode* leftChild = nullptr;
      TreeNode* rightChild = nullptr;
   };

   struct KDTreeNDimensionalSorter              //Vector(0), index(1), sortAxis(2)
   {  bool operator()(const std::tuple< const Vector&, unsigned int, unsigned int >& a,
                      const std::tuple< const Vector&, unsigned int, unsigned int >& b) const
      {
         if( std::get<2>(b) == 0 )      //x axis
         {
            if( std::get<0>(a).x == std::get<0>(b).x )
               return std::get<1>(a) < std::get<1>(b);
            return std::get<0>(a).x < std::get<0>(b).x;
         }
         else if( std::get<2>(b) == 1 ) //y axis
         {
            if( std::get<0>(a).y == std::get<0>(b).y )
               return std::get<1>(a) < std::get<1>(b);
            return( std::get<0>(a).y < std::get<0>(b).y );
         }
         else                     //z axis
         {
            if( std::get<0>(a).z == std::get<0>(b).z )
               return std::get<1>(a) < std::get<1>(b);
            return( std::get<0>(a).z < std::get<0>(b).z );
         }
      }
   };

public:
   ModelKDTreeOfVertices( const std::vector< Vector >& verts, const std::vector< unsigned int >& indicies );
   virtual ~ModelKDTreeOfVertices();

   void printKDTree( std::ostream& os );
   
   /**
      \return The Index into the Model:compositeVertexList corresponding to the
      vertex which is closest to the in passed vertex p. This has computational
      complexity on average of O(log N).
   */
   std::pair< unsigned int, float > findNearestPointInThisPointSet( const Vector& p );

   static const unsigned int NUM_DIMENSIONS = 3; ///< KD Tree sorts on 3D Vectors

protected:

   Model* m;
   TreeNode* root;
   TreeNode* buildKDTree( const std::vector< Vector >& v, std::vector< unsigned int >& i, unsigned int depth );
   void recNNSearch( TreeNode* n, const Vector& vec, unsigned int depth, 
                     unsigned int& currMinIndex, float& currMinDistSq );
   float findShortestDistFromVecToHyperPlaneViaSortAxis( const Vector& vec, 
                                                         const Vector& node, unsigned int sortAxis );
   bool ifALessThanBViaSortAxis( const Vector& a, Vector* b, unsigned int sortAxis );
   float computeDistanceSquaredBetween2Points( const Vector& a, const Vector& b );
   void recWalkKDTree( TreeNode* n, std::ostream& os, unsigned int depth );

   /**
      Sorts the index list by axis and returns the index into the 'index vector' which
      is the median. Hence, int x = findMedian( v, i, axis); medianIndex = i[x];
   */
   unsigned int findMedian( const std::vector< Vector >& v, std::vector< unsigned int >& i, unsigned int sortAxis );

   const std::vector< Vector >& verts; ///< Pointer to Model::compositeVertexList
   const std::vector< unsigned int >& indicies; ///< Pointer to Model::compositeIndexList
   std::set< unsigned int > uniqueIndicies; ///< Set of sorted unique indicies
};

} //namespace Aftr

