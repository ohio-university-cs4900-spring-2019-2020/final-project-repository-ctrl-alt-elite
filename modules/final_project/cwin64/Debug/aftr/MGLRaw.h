#pragma once

#include "MGL.h"

namespace Aftr
{
   class MGLRaw : public MGL
   {
   public:
      static MGLRaw* New( WO* parent, float* vertices, unsigned int size );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~MGLRaw();
      virtual void render( const Camera& cam );
   protected:
      MGLRaw( WO* parent );
      virtual void onCreate( float* vertices, unsigned int size ); 
   };
};

