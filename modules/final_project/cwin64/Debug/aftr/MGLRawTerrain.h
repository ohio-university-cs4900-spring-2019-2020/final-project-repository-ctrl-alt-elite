#pragma once

#include "MGL.h"

namespace Aftr
{
   class MGLRawTerrain : public MGL
   {
   public:
      static MGLRawTerrain* New( WO* parent, float* vertices, unsigned int x, unsigned int y, double xIgnoredPercentage, double yIgnoredColorPercentage );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~MGLRawTerrain();
      virtual void render( const Camera& cam );
   protected:
      MGLRawTerrain( WO* parent );
      virtual void onCreate( float* vertices, unsigned int x, unsigned int y, double xIgnoredPercentage, double yIgnoredColorPercentage ); 
   };
};

