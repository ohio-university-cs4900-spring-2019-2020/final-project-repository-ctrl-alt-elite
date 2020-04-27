#pragma once

#include "WO.h"

namespace Aftr
{
   class WORawGLLines : public WO
   {
   public:
      static WORawGLLines* New( float* vertices, unsigned int numVertices );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      static WORawGLLines* New( float* vertices, float* colors, unsigned int numVertices );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~WORawGLLines();
   protected:
      WORawGLLines();
      virtual void onCreate( float* vertices, unsigned int numVertices ); 
      virtual void onCreate( float* vertices, float* colors, unsigned int numVertices ); 
   };
};

