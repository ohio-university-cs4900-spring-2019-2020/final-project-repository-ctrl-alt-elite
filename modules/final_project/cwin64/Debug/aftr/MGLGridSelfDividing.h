#pragma once
#include "MGLGrid.h"

namespace Aftr
{

   class MGLGridSelfDividing : public MGLGrid
   {  
   public:
      MGLGridSelfDividing( WO* parentWO, float x, float y, float z, float t, int n, int s);
      virtual ~MGLGridSelfDividing();
      void update();
   protected:
      GLint sizeIndices;//length of list list
      GLint sizeVertices;//length of description list
      int counter;
      float thresh;	 
      size_t sizeL;
      size_t sizeD;
      GLint* subList;
      void setFidelity(int n);
   };

}