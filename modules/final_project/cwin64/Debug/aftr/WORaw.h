#pragma once

#include "WO.h"

namespace Aftr
{
   class WORaw : public WO
   {
   public:
      static WORaw* New( float* vertices, unsigned int size );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      virtual ~WORaw();
   protected:
      WORaw();
      virtual void onCreate( float* vertices, unsigned int size ); 
   };
};

