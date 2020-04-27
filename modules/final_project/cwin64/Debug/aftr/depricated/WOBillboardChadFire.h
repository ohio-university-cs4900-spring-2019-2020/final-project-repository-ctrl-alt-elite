#pragma once


#include "WOBillboard.h"
#include "MGLBillboardChadFire.h"

namespace Aftr
{

   /**
   \author Chad Mourning
   */
   class Camera;
   class WOBillboardChadFire : public WOBillboard
   {

   public:
      static WOBillboardChadFire* New(const std::vector<std::string>& textures, Camera** cam, float height = 1, float width = 1, unsigned int updatetimer = 100, int startFrame = 0);
      virtual ~WOBillboardChadFire();
      virtual void onPhysicsEngineTick();
   protected:
      virtual void onCreate(const std::vector<std::string>& textures, Camera** cam, float height, float width, int startFrame);
WOBillboardChadFire(unsigned int updateTimer //update timer in milliseconds
         );
       /**The frequency the fire texture will be updated*/
      int updateTimer;
      /**Last updated time*/
      int internalTimer;



   };




}  //namespace Aftr


