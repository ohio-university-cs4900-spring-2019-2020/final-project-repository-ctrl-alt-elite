#pragma once

#include <vector>
#include <map>
#include "VectorFwd.h"


/*************************************************************************
 SLN 22 Nov 2016: This class is deprecated and should no longer be used...
 Consider AftrMotionData for dynamically updating pose of a WO.
 ************************************************************************/

namespace Aftr
{

struct AftrItineraryEvent
{
   Vector* position;
   float* orientation;
};

class AftrItinerary
{
public:
   AftrItinerary( std::vector<Vector*> positions = std::vector<Vector*>(), std::vector<float*> orientations = std::vector<float*>(), std::vector<unsigned int> times = std::vector<unsigned int>() );
   void addEvent( Vector* position, float* orientation, unsigned int time );
   void addEvents( std::vector<Vector*> positions, std::vector<float*> orientations, std::vector<unsigned int> times );
   virtual ~AftrItinerary();
   AftrItineraryEvent getEventAtTime( unsigned int time );
   void addOffset( const Vector& offset );///< adds a global coordinate offset to the current list (cumulative)
   std::vector<Vector*> getPoints();
   std::map<unsigned int, AftrItineraryEvent >* getEvents() { return &events; }
protected:
   std::map<unsigned int, AftrItineraryEvent > events;
};

}

