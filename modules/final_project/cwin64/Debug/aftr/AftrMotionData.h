#pragma once

#include "VectorFwd.h"

namespace Aftr
{

class AftrMotionData
{
public:
   AftrMotionData();
   virtual ~AftrMotionData();
   virtual Vector getPositionAtParametricOffset( double p ) = 0;
   virtual void getOrientationAtParametricOffset( double p, float outM[16] ) = 0;
   virtual void getPoseAtParametricOffset( double p, Vector& outPos, float outM[16] ) = 0;
};

}

