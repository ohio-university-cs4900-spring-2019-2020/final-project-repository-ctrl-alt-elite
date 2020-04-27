#pragma once


#include "ExtrusionWeights.h"

namespace Aftr
{

class ExtrusionWeightsThirds : public ExtrusionWeights
{
public:
   //using ExtrusionWeights::ExtrusionWeights;//attempt to use C++ 0x forward construcotr, didn't seem to work
   ExtrusionWeightsThirds(const std::vector< ModelMesh* >& meshes, const std::vector< std::vector< GridNode > >& graph, int i, int j);
    virtual void updateWeights(bool printDebugOutput = false) override;//attempting to use C++ 0x override notation to indicate this is an overridden virtual function, not the base declaration
};

}

