#pragma once
#include "WO.h"

namespace Aftr
{
   class WORawQuads : public WO
   {
   public:
      /**
         No per-vertex colors, one skin is used to set the WO's color
      */
      static WORawQuads* New( float* vertices, unsigned int numQuads );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      /**
         Per-vertex colors
      */
      static WORawQuads* New( float* vertices, unsigned int numQuads, const std::vector< aftrColor4ub >& perVertexColors );
      virtual ~WORawQuads();
   protected:
      WORawQuads();
      virtual void onCreate( float* vertices, unsigned int numQuads );
      virtual void onCreate( float* vertices, unsigned int numQuads, const std::vector< aftrColor4ub >& perVertexColors );
   };
};