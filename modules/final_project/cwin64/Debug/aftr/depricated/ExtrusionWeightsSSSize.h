#pragma once

#include "ExtrusionWeights.h"
#include "GridTopology.h"
#include "AftrOpenGLIncludes.h"
#include <vector>

namespace Aftr
{
  

class ExtrusionWeightsSSSize : public ExtrusionWeights
{
public:
   ExtrusionWeightsSSSize( const std::vector< ModelMesh* >& meshes, const std::vector< std::vector< GridNode > >& graph, int i, int j );
    virtual void updateWeights( bool printDebugOutput = false);
protected:
   double findLeftFaceWeight();
   double findRightFaceWeight();
   double findMainLeftToRightWeight();
   double findBackFaceWeight();
   double findFrontFaceWeight();
   double findWeight( GLfloat* first, GLfloat* second );

   
};

}

