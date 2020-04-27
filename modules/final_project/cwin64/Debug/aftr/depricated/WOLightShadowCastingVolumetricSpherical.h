#pragma once

#include "WOLightShadowCasting.h"
#include <set>

namespace Steamie
{

      class IFaceShadowCaster;

class WOLightShadowCastingVolumetricSpherical : public WOLightShadowCasting
{
   
public:
   static WOLightShadowCastingVolumetricSpherical* New(std::vector<IFaceShadowCaster*> shadowList = std::vector<IFaceShadowCaster*>(), float radius = 1, int sampleSize = 1, GLfloat diffuseRed = 1, GLfloat diffuseGreen = 1, GLfloat diffuseBlue = 1, GLfloat diffuseAlpha = 1,
              GLfloat ambientRed = 0, GLfloat ambientGreen = 0, GLfloat ambientBlue = 0, GLfloat ambientAlpha = 1,
              GLfloat specularRed = 1, GLfloat specularGreen = 1, GLfloat specularBlue = 1, GLfloat specularAlpha = 1);
   virtual ~WOLightShadowCastingVolumetricSpherical();
   virtual void castShadows();
protected:
   WOLightShadowCastingVolumetricSpherical(std::vector<IFaceShadowCaster*> shadowList = std::vector<IFaceShadowCaster*>(), float radius = 1, int sampleSize = 1, GLfloat diffuseRed = 1, GLfloat diffuseGreen = 1, GLfloat diffuseBlue = 1, GLfloat diffuseAlpha = 1,
              GLfloat ambientRed = 0, GLfloat ambientGreen = 0, GLfloat ambientBlue = 0, GLfloat ambientAlpha = 1,
              GLfloat specularRed = 1, GLfloat specularGreen = 1, GLfloat specularBlue = 1, GLfloat specularAlpha = 1);
   float radius;
   std::vector<Vector> samplePositions;
};

}

