#pragma once

#include "WO.h"

namespace Aftr
{
   class AftrItineraryPerFrameCamInterpolation;
   class Camera;

   class WOOperatorItineraryPerFrameCamInterpolation : public WO
   {
   public:
      /**
         This retains ownership of the itinerary, but not the itineraree.
      */
      static WOOperatorItineraryPerFrameCamInterpolation* New( 
            Camera** cam, AftrItineraryPerFrameCamInterpolation* itinerary );

      virtual ~WOOperatorItineraryPerFrameCamInterpolation();
      virtual void onUpdateWO();
      void begin() { this->go = true; }
      void pause() { this->go = false; }
      void toggle() { this->go = !this->go; }
      void reset() { this->currFrame = 0; }
      void goBackward() { this->GoForward = false; }
      void goForward() { this->GoForward = true; }
      void toggleDirection() { this->GoForward = !this->GoForward; }
      void captureEachFrameToFile( bool performCapture ) { this->performFrameCapture = performCapture; }
      bool captureEachFrameToFile() { return this->performFrameCapture; }


   protected:
      virtual void onCreate();
      WOOperatorItineraryPerFrameCamInterpolation(Camera** cam, AftrItineraryPerFrameCamInterpolation* itinerary);
      Camera** cam;
      AftrItineraryPerFrameCamInterpolation* itinerary;
      unsigned int currFrame;
      bool GoForward;
      bool go;
      bool performFrameCapture;
   };
}

