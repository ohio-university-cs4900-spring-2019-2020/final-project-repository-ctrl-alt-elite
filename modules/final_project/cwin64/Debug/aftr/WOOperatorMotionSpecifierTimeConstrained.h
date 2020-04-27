#pragma once

#include "WOOperatorMotionSpecifier.h"

namespace Aftr
{
class AftrMotionData;

class WOOperatorMotionSpecifierTimeConstrained : public WOOperatorMotionSpecifier
{
public:
   /**
      This abstract class serves as a base WOOperator which specifies motion that
      can be applied on to a WO given a set of AftrMotionData.
      This takes ownership of the AftrMotionData* data, but not the
      WO* actor to which the motion data is applied.
   */
   static WOOperatorMotionSpecifierTimeConstrained* New( WO* actor, AftrMotionData* data, unsigned int timeDurationMilliSeconds );
   virtual ~WOOperatorMotionSpecifierTimeConstrained();
   virtual void onUpdateWO();

   /// Jump to any parametric offset [0,1] within the motion data
   virtual void setMotionOffset( double t );
   /// Return the current parametric offset within the motion data
   virtual double getMotionOffset();

   virtual void setMotionTimeDurationMilliSeconds( unsigned int timeMilliSeconds );
   virtual unsigned int getMotionTimeDurationMilliSeconds();

protected:
   WOOperatorMotionSpecifierTimeConstrained( WO* actor, AftrMotionData* motionDat, unsigned int timeDurationMilliSeconds );
   virtual void onCreate();

   double p = 0; ///< parametric distance [0,1] through motion described in motionDat
   double elapsedTimeMilliSeconds = 0;
   unsigned int timeDurationMilliSeconds = 0;;
};
}

