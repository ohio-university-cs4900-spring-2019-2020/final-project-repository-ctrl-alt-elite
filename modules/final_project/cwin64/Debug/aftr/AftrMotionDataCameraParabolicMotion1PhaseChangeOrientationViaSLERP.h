#pragma once

#include "AftrMotionData.h"
#include "Vector.h"
#include "Quat.h"

namespace Aftr
{

class AftrMotionDataCameraParabolicMotion1PhaseChangeOrientationViaSLERP : public AftrMotionData
{
public:
   AftrMotionDataCameraParabolicMotion1PhaseChangeOrientationViaSLERP(
                                                const Quat& startOrient, 
                                                const Quat& endOrient,
                                                const Vector& constPos );
   virtual ~AftrMotionDataCameraParabolicMotion1PhaseChangeOrientationViaSLERP();
   virtual Vector getPositionAtParametricOffset( double p );
   virtual void getOrientationAtParametricOffset( double p, float outM[16] );
   virtual void getPoseAtParametricOffset( double p, Vector& outPos, float outM[16] );

protected:
   Vector constPos; ///< Constant non-changing position for this motion specifier, since this only deals w/ orientation

   Quat qStartOrient;
   Quat qEndOrient;
};

}

