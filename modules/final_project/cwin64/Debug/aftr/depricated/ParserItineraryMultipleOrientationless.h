#pragma once

#include <vector>
#include <string>

namespace Aftr
{
   class AftrItinerary;

   class ParserItineraryMultipleOrientationless
   {
      public:
         ParserItineraryMultipleOrientationless();
         virtual ~ParserItineraryMultipleOrientationless();
         /**

         Each call to parsefile gets a new copy to the vector of itineraries, which the caller owns.

         */
         std::vector<AftrItinerary*>* parseFile( const std::string& filename, unsigned int numObjects);
   };

}

