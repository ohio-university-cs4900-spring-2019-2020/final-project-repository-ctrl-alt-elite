#pragma once

#include <vector>

namespace Aftr
{

    class ModelMesh;
   struct GridNode;

class ExtrusionWeights
{
public:
   ExtrusionWeights( const std::vector< ModelMesh* >& meshes, const std::vector< std::vector< GridNode > >& graph, int i, int j );
   virtual ~ExtrusionWeights() {}
   virtual void updateWeights(bool printDebugOutput = false) = 0;
   double getLeftWeight() { return leftWeight; }
   double getRightWeight() { return rightWeight; }
   double getFrontWeight() { return frontWeight; }
   double getBackWeight() { return backWeight; }
   double getMainWeightLeftToRight() { return mainWeightLeftToRight; }
   double getMainWeightFrontToBack() { return mainWeightFrontToBack; }
protected:
   double leftWeight;
   double rightWeight;
   double frontWeight;
   double backWeight;
   double mainWeightLeftToRight;
   double mainWeightFrontToBack;

     std::vector< ModelMesh* > meshes;
    std::vector< std::vector< GridNode > > graph;
   int i;
   int j;
};

}

