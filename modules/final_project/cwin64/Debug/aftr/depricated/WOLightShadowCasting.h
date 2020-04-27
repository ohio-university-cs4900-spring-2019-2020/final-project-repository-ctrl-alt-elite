#pragma once

#include "WOLight.h"
#include <string>

namespace Steamie
{

   class MGLLight;
   class WOShadowCaster;
   class IFaceShadowCaster;

   /**
   \author Chad Mourning

   This class abstracts the behavior of OpenGL lights to act in a similar manner to the engines World Objects.
   Additionally to the normal WOLight this has a list of objects on which it will (Attempt) to cast shadows.
   */
   class WOLightShadowCasting : public WOLight
   {
   public:	
      /**
      Constructor

      
      */
      static WOLightShadowCasting* New(std::vector<IFaceShadowCaster*> shadowList = std::vector<IFaceShadowCaster*>(), GLfloat diffuseRed = 1, GLfloat diffuseGreen = 1, GLfloat diffuseBlue = 1, GLfloat diffuseAlpha = 1,
              GLfloat ambientRed = 0, GLfloat ambientGreen = 0, GLfloat ambientBlue = 0, GLfloat ambientAlpha = 1,
              GLfloat specularRed = 1, GLfloat specularGreen = 1, GLfloat specularBlue = 1, GLfloat specularAlpha = 1);
      
      /**
      Destructor
      */

      virtual ~WOLightShadowCasting();   
      virtual void onSimulationCompletelyInitialized();
      std::vector<IFaceShadowCaster*>* getShadowList() { return &shadowList; }
      virtual void castShadows();
      void useZFail() { zfail = true; }
      void useZPass() { zfail = false; }
   protected:
      WOLightShadowCasting(std::vector<IFaceShadowCaster*> shadowList = std::vector<IFaceShadowCaster*>(), GLfloat diffuseRed = 1, GLfloat diffuseGreen = 1, GLfloat diffuseBlue = 1, GLfloat diffuseAlpha = 1,
              GLfloat ambientRed = 0, GLfloat ambientGreen = 0, GLfloat ambientBlue = 0, GLfloat ambientAlpha = 1,
              GLfloat specularRed = 1, GLfloat specularGreen = 1, GLfloat specularBlue = 1, GLfloat specularAlpha = 1);
      bool zfail;
      void beginShadowSetup();
      void endShadowSetup(size_t numSamples = 1);
      void beginZPass();
      void beginZFail();
      std::vector<IFaceShadowCaster*> shadowList;
   };

}

