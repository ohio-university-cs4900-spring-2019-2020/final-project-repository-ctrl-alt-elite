#pragma once

namespace Aftr
{

   class WO;
   class Camera;

   class IFaceBillboard
   {
   public:
      IFaceBillboard( WO* wo );
   protected:
      //Automatically alters the display matrix such that the objects YZ plane is oriented towards cam
      //The User is advised to glPushMatrix() before use and after rendering.
      void billboardMeTowardsCamera( Camera* cam );

	  void billboardMeOppositeToCamera( Camera* cam );
      WO* iFaceBillboardWO;
   };

}

