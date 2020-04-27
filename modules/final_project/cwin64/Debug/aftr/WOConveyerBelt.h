#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE

#include "WOStatic.h"

namespace Aftr
{

      //texture orientation types, incomplete
   enum TextureOrientationType { totXYZ, totYXZ, totY_XZ, totNUM_TYPES };

   class TextureOrientation
   {
   public:
      TextureOrientationType type;
       Vector convert(Vector v);
   protected:
   };

class WOConveyerBelt : public WOStatic
{
public:
   static WOConveyerBelt* New(const std::string& filename, const Vector& forceDirection, float speed, TextureOrientationType type, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   virtual ~WOConveyerBelt();
   virtual void onUpdateWO();
   void setSpeed(float speed);
   void setForceDirection(Vector direction);
   virtual void ODEupdateForcesAndJoints();
protected:
   virtual void onCreate(const std::string& filename, const Vector& scale, MESH_SHADING_TYPE shadingType);
   WOConveyerBelt(const Vector& forceDirection, float speed, TextureOrientationType type);
   void updateSurface();
   float speed;
   Vector forceDirection;
   TextureOrientation type;
   Vector textureRatios;
};

}



#endif
