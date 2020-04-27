#pragma once

#include "WO.h"
#include <vector>

namespace Aftr
{

      /**
   \author Chad Mourning
   */

   class WOFade : public WO
   {
   public:
      /**
      \param colorsToUseInFadeArray A transition from element i to j will make the screen fade from color i to color j
      */
      static WOFade* New(const std::vector<Vector>& colorsToUseInFadeArray);
      
      virtual ~WOFade() {}
      ///used for a single transition
      virtual void fade(int i, int j, unsigned int transitionTime);
      ///used for multiple transitions
      virtual void fade(std::vector<int> state1, std::vector<int> state2, std::vector<unsigned int> transitionTimes);
      virtual void onPhysicsEngineTick();
   protected:
      WOFade();
      virtual void onCreate(const std::vector<Vector>& colorsToUseInFadeArray);
   };

}

