#pragma once

#include "WO.h"

namespace Aftr
{
   class WORawPolyline : public WO
   {
   public:
      static WORawPolyline* New( float* vertices, unsigned int size );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      static WORawPolyline* New( float* vertices, float* colors, unsigned int size );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~WORawPolyline();
   protected:
      WORawPolyline();
      virtual void onCreate( float* vertices, unsigned int size ); 
      virtual void onCreate( float* vertices, float* colors, unsigned int size ); 
   };
};

