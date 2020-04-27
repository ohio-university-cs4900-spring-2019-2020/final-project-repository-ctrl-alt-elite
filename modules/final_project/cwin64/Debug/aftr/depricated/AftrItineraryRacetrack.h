#pragma once

#include "AftrItinerary.h"

namespace Aftr
{

   class AftrItineraryRacetrack : public AftrItinerary
   {
      public:
         AftrItineraryRacetrack(Vector* initialPoint, Vector* initialHeading, Vector* initialNormal, bool calcNow = true);
         virtual ~AftrItineraryRacetrack();
         void calc();
         float majorAxis;
         float minorAxis;
         unsigned int majorAxisTime;
         unsigned int minorAxisTime;
         float bankAngle;
      protected:
         Vector* initialPoint;
         Vector* initialHeading;
         Vector* initialNormal;
         void generatePoints();
         void generateOrientations();
         void calculateMatrix(float * m);
         void modifyPoints(float* m);
   };

}

