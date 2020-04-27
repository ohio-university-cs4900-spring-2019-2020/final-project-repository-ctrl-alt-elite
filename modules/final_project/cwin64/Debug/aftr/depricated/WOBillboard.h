#pragma once

#include "WO.h"
#include <string>
#include <vector>

namespace Aftr
{
   class GLView;
   class Camera;

   /**
   \author Chad Mourning (Updated by Scott Nykl)
      This class is used to create simple textured planes that billboard themsevles towards the camera in the x-y plane.
   */
   class WOBillboard : public WO
   {
   public:	
      static WOBillboard* New(const std::vector<std::string>& textures, Camera** cam, int slices = 1, float height = 1, float width = 1);
      /**
      Destructor
      */
      virtual ~WOBillboard();
   protected:
      virtual void onCreate(const std::vector<std::string>& textures, Camera** cam, int slices, float height, float width);
      WOBillboard();
   };

}

