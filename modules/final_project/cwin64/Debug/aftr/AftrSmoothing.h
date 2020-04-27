#pragma once

#include "VectorFwd.h"

namespace Aftr
{

class AftrSmoothing
{
public:
   /**
      Assumes Roll is in X component, Pitch is Y component, and Yaw is Z component. This smoothes assuming that
      motion is about a unit circle and the Roll and Yaw components vary from [0,180),(-180,-0). Therefore, a linear
      discontinuity occurs at 180/-180 (coincident points). This smoothing method will correct for that discontinuity
      thereby behaving just like applyLowPassFilter, except this works on the unit circle.
   */
   static VectorD applyLowPassFilterToRollPitchYaw( const VectorD& unfilteredRPY, const VectorD& filteredRPYOld,
                                                    double freqHz = 20.0, double timeConstInSeconds = 0.3 );

   static double applyLowPassFilterToRollPitchYaw( double unfilteredRPY, double filteredRPYOld,
                                                   double freqHz = 20.0, double timeConstInSeconds = 0.3 );

   static double applyLowPassFilter( double unfiltered, double filteredOld, 
                                     double freqHz = 20.0, double timeConstInSeconds = 0.3 );

   static VectorD applyLowPassFilter( const VectorD& unfiltered, const VectorD& filteredOld, 
                                      double freqHz = 20.0, double timeConstInSeconds = 0.3 );

};

}


