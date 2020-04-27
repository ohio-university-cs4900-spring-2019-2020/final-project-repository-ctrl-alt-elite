#pragma once

#include "AftrItinerary.h"
#include "Vector.h"

namespace Aftr
{

class AftrItineraryPerFrameCamInterpolation
{
public:
   AftrItineraryPerFrameCamInterpolation( const Vector& startPos, const Vector& endPos, unsigned int numFrames );
   virtual ~AftrItineraryPerFrameCamInterpolation();
   
   std::map<unsigned int, AftrItineraryEvent >* getEvents() { return &events; }
   AftrItineraryEvent getEventAtFrame( unsigned int frameNum );
protected:

   void generateInterpolationData();
   void destroyEventsMap();

   std::map<unsigned int, AftrItineraryEvent > events;
   Vector startPos;
   Vector endPos;
   unsigned int numFrames;
};

}

