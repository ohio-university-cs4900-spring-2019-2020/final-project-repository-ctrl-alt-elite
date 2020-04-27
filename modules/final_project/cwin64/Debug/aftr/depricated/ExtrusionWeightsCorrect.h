#pragma once


#include "ExtrusionWeights.h"
#include "GridTopology.h"
#include <vector>

namespace Aftr
{
   class ModelMesh;
  
class ExtrusionWeightsCorrect : public ExtrusionWeights
{
public:
   ExtrusionWeightsCorrect( const std::vector< ModelMesh* >& meshes, const std::vector< std::vector< GridNode > >& graph, int i, int j );
   virtual void updateWeights(bool printDebugOutput = false);
protected:
  
};

}

