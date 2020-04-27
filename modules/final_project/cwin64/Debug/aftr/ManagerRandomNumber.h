/**
   \class ManagerRandomNumber
   \author Scott Nykl
   \brief A static manager to get random numbers, in a cross platform, cross networked manner.
*/

#pragma once

namespace Aftr
{

class ManagerRandomNumber
{
public:

   static void init();

   static int getRandomInt( int minValInclusive, int maxValInclusive );
   static unsigned int getRandomUnsignedInt( unsigned int minValInclusive, unsigned int maxValInclusive );
   static float getRandomFloat( float minValInclusive, float maxValInclusive );
   static double getRandomDouble( double minValInclusive, double maxValInclusive );//seems like this should return a double

protected:
   static unsigned int seed;



};

} //namespace Aftr


