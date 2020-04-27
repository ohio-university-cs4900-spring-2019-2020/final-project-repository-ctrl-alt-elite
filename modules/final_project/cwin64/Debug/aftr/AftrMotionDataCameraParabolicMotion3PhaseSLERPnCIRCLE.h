#pragma once

#include "AftrMotionData.h"
#include "Vector.h"
#include "Quat.h"

namespace Aftr
{

class AftrMotionDataCameraParabolicMotion3PhaseSLERPnCIRCLE : public AftrMotionData
{
public:
   AftrMotionDataCameraParabolicMotion3PhaseSLERPnCIRCLE( const Vector& startPos, 
                                                      const Quat& startOrient,
                                                      const Vector& normalDirectionDefiningParabolicApexDir,
                                                      const Vector& endLookAtPt,
                                                      const Vector& endPosition );
   virtual ~AftrMotionDataCameraParabolicMotion3PhaseSLERPnCIRCLE();
   virtual Vector getPositionAtParametricOffset( double p );
   virtual void getOrientationAtParametricOffset( double p, float outM[16] );
   virtual void getPoseAtParametricOffset( double p, Vector& outPos, float outM[16] );
   virtual void setParametricDistanceOfLowerBound( float lowerBound );
   virtual void setParametricDistanceOfUpperBound( float upperBound );

protected:
   Vector ap; ///< Start Pos
   Vector bp; ///< End Pos

   Vector midPt;
   Vector radius; ///< Arc arm that is rotated through space
   Vector relz; ///< Normal direction defining direction towards apex of parabolic arc relative to bp - ap
   Vector relx; ///< Vector pointing at endPos from startPos
   Vector rely; ///< relz (cross) relx

   double LB;
   double UB;

   Quat qStartOrient;
   Quat qAtLB;

   //end params
   Vector endPosition;
   Vector endLookAtPt;
};

}

