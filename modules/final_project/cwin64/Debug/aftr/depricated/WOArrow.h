#pragma once

#include "WO.h"

namespace Aftr
{
   enum ARROW_MODE { amVANISH = 0, amRESET, amPERSIST, amNUM_MODES };

   class Camera;

   /**
   
   \class WOArrow
   \author Chad Mourning
   \brief An arrow that can scale with distance, blink, and attach to objects.

   */

   class WOArrow : public WO
   {
   public:
      /**

      The constructor for the WOArrow class:

      \param scale Scale factor from the default size
      \param color Vector representation of the color (no alpha support)
      \param scaleWithDistance if true the arrow will remain the same size on screen no matter the distance
      \param cam A point to the camera (only used if scale with distance is enabled)
      \param blink if true the arrow will blink
      \param blinkTimer if blink is true this is the blinking interval

      */
      static WOArrow* New(float scale, Vector color, bool scaleWithDistance = false, Camera** cam = NULL, bool blink = false, unsigned int blinkTimer = 0);
      static WOArrow* New(float scale, Vector color, WO* followee, Vector offset, bool scaleWithDistancce = false, Camera** cam = NULL, bool blink = false, unsigned int blinkTimer = 0);
      /**

      The same as above except:

      \param followee The WO to lock onto.
      \param offset The distance away from the object to stay locked to.

      */
      virtual void onPhysicsEngineTick();
      virtual ~WOArrow() {};

      void enableBlinking() { blink = true; }
      void disableBlinking() { blink = false; }
      void toggleBlinking() { blink = !blink; }
      void setBlinking(bool blink) { this->blink = blink;}
      bool getBlinking() { return blink; }

      void setBlinkTimer(unsigned int x) { blinkTimer = x; }
      unsigned int getBlinkTimer() { return blinkTimer; }

      //make sure followers are set to NULL, before deleting it
      void setFollowee(WO* followee);
      WO* getFollowee();

      void setArrowMode(ARROW_MODE mode) { this->mode = mode; }
      ARROW_MODE getArrowMode() { return this->mode; }

   protected:
      WOArrow(float scale, Vector color, bool scaleWithDistance = false, Camera** cam = NULL, bool blink = false, unsigned int blinkTimer = 0);
      WOArrow(float scale, Vector color, WO* followee, Vector offset, bool scaleWithDistance = false, Camera** cam = NULL, bool blink = false, unsigned int blinkTimer = 0);
      virtual void onCreate(float scale, Vector color, bool scaleWithDistance, Camera** cam);
      bool blink;
      unsigned int blinkTimer;
      unsigned int internalTimer;

      ARROW_MODE mode;
   };

}

