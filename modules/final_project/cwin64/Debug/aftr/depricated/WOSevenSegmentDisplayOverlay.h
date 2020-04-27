#pragma once

#include "WO.h"

namespace Aftr

/**

   \author Chad Mourning

  */
{

   class WOSevenSegmentDisplayOverlay : public WO
   {
   public:
      static WOSevenSegmentDisplayOverlay* New(float height, float width);
      virtual ~WOSevenSegmentDisplayOverlay();
      void increment();
      void decrement();
      void setValue(unsigned int x);
   protected:
      virtual void onCreate(float height, float width);
      WOSevenSegmentDisplayOverlay();
   };

}

