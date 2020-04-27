#pragma once

#include "MGL.h"
#include <vector>
#include <queue>

namespace Aftr
{
   class WO;
      class IndexedGeometryQuad;

   class MGLFade : public MGL
   {
   public:
      MGLFade( WO* parentWO, std::vector<Vector> colors);
      virtual ~MGLFade();
      virtual void render( const Camera& cam );
      virtual void scheduler(unsigned int timeSinceLastCall);
      virtual void fade(int i, int j, unsigned int transitionTime);
      virtual void fade(std::vector<int> i, std::vector<int> j, std::vector<unsigned int> transitionTimes);
   protected:
      std::vector<Vector> fadeArray;
      unsigned int internalTimer;
      unsigned int transitionTime;
      int state1;
      int state2;
      std::queue<int> first;
      std::queue<int> second;
      std::queue<unsigned int> times;
      IndexedGeometryQuad* quad;
   };

}

