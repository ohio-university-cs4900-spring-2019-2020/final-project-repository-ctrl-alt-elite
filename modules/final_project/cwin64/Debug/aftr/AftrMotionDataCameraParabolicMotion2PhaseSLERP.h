#pragma once

#include "AftrMotionData.h"
#include "Vector.h"
#include "Quat.h"

namespace Aftr
{

class AftrMotionDataCameraParabolicMotion2PhaseSLERP : public AftrMotionData
{
public:
   AftrMotionDataCameraParabolicMotion2PhaseSLERP( const Vector& startPos, const Vector& endPos, 
                                                      const Quat& startOrient, 
                                                      const Quat& endOrient,
                                                      const Vector& normalDirectionDefiningParabolicApexDir );
   virtual ~AftrMotionDataCameraParabolicMotion2PhaseSLERP();
   virtual Vector getPositionAtParametricOffset( double p );
   virtual void getOrientationAtParametricOffset( double p, float outM[16] );
   virtual void getPoseAtParametricOffset( double p, Vector& outPos, float outM[16] );

   

protected:
   Vector ap; ///< Start Pos
   Vector bp; ///< End Pos
   //Quat aq; ///< Start orientation
   Quat bq; ///< End orientation

   Vector midPt;
   Vector radius; ///< Arc arm that is rotated through space
   Vector relz; ///< Normal direction defining direction towards apex of parabolic arc relative to bp - ap
   Vector relx; ///< Vector pointing at endPos from startPos
   Vector rely; ///< relz (cross) relx

   double LB; ///< Lower bound. Before this parametric time, the camera is only changing its lookDir towards endPoint
   double UB; ///< Upper bound. After LB and before UB, camera is moving along parabolic arc looking at endPoint

   Quat qStartOrient;
   Quat qAtLB;
   Quat qAtUB;
   Quat qEndOrient;
};

}

