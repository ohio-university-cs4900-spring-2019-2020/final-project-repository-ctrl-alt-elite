#pragma once

#include "MGL.h"

namespace Aftr
{
   class MGLRawGLLines : public MGL
   {
   public:
      static MGLRawGLLines* New( WO* parent, float* vertices, unsigned int numVertices );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      static MGLRawGLLines* New( WO* parent, float* vertices, float* colors, unsigned int numVertices );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~MGLRawGLLines();
      virtual void render( const Camera& cam );
   protected:
      MGLRawGLLines( WO* parent );
      virtual void onCreate( float* vertices, unsigned int numVertices );
      virtual void onCreate( float* vertices, float* colors, unsigned int numVertices );
   };
};

