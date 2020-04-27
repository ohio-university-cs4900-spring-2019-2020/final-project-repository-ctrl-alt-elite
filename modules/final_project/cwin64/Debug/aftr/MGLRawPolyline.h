#pragma once

#include "MGL.h"

namespace Aftr
{
   class MGLRawPolyline : public MGL
   {
   public:
      static MGLRawPolyline* New( WO* parent, float* vertices, unsigned int size );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      static MGLRawPolyline* New( WO* parent, float* vertices, float* colors, unsigned int size );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~MGLRawPolyline();
      virtual void render( const Camera& cam );
   protected:
      MGLRawPolyline( WO* parent );
      virtual void onCreate( float* vertices, unsigned int size ); 
      virtual void onCreate( float* vertices, float* colors, unsigned int size );
   };
};

