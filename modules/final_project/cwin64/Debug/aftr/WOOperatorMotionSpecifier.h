#pragma once

#include "WO.h"

namespace Aftr
{
class AftrMotionData;

class WOOperatorMotionSpecifier : public WO
{
public:
   /**
      This abstract class serves as a base WOOperator which specifies motion that
      can be applied on to a WO given a set of AftrMotionData.
      This takes ownership of the AftrMotionData* data, but not the
      WO* actor to which the motion data is applied.

      Each subclass must overload onUpdateWO, setMotionOffset, getMotionOffset.
   */
   //static WOOperatorMotionSpecifier* New( WO* actor, AftrMotionData* data );
   virtual ~WOOperatorMotionSpecifier();
   virtual void onUpdateWO();

   /// Jump to any parametric offset [0,1] within the motion data
   virtual void setMotionOffset( double t ) = 0;
   /// Return the current parametric offset within the motion data
   virtual double getMotionOffset() = 0;

   
   /// Begin applying the corresponding motion data to the actor.
   /// Any location within the motion may be specified via setMotionOffset.
   virtual void startMotion();
   /// Stop applying the corresponding motion data to the actor. The point where
   /// the motion was stopped is remembered and can be resumed by invoking startMotion.
   /// Any location within the motion may be specified via setMotionOffset.
   virtual void stopMotion();

   /// Pause or unpause the motion
   virtual void toggleMotion();

   /// Returns true iff the motion data is currently being applied to the actor.
   /// That is, the motion is not currently paused/stopped/halted.
   virtual bool isMotionAnimated();
   /// Same as calling startMotion / stopMotion, except settable via a bool.
   virtual void isMotionAnimated( bool animateMotion );

   /// Sets a multiplier that scales the rate at which the motion data is displayed
   virtual void setMotionPlaybackSpeed( double timeMultiplier );
   /// Returns the multiplier used to scale the rate at which the motion data is displayed
   virtual double getMotionPlaybackSpeed();
   /// Negates the multiplier so the motion data is displayed in the reverse direction
   /// from which it is currently playing
   virtual void toggleMotionDirection();

   /// Changes the motion data set to the new data set. Any existing motion data is deleted.
   virtual void setMotionData( AftrMotionData* motionDat );

   virtual void setMotionActor( WO* motionActor );
   virtual WO* getMotionActor();

protected:
   WOOperatorMotionSpecifier( WO* actor, AftrMotionData* motionDat );
   virtual void onCreate();

   WO* motionActor = nullptr; ///< The WO upon which this.motionDat is applied. Not owned by this instance
   AftrMotionData* motionDat = nullptr; ///< Data that describes the position / orientation that this operator applies onto 'this.actor'. Owned by this instance.
   double motionTimeMultiplier = 1.0; ///< "fast-forward", "re-wind", scalar that determines playback speed
   bool motionIsAnimating = false;; ///< True, when the motion is actively being applied to the actor, false otherwise.
};
}

