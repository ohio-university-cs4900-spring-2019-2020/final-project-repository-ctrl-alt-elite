#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "IFaceODE.h"
#include <map>

namespace Aftr
{

/** \class IFaceODECollisionLoggerSink
    \brief An interface used by any WO that records the velocities
    of this object after a collision.

    \{
*/
class IFaceODECollisionLoggerSink : public virtual IFaceODE
{
public:
   IFaceODECollisionLoggerSink( WO* woUsingThisInterface );
   virtual ~IFaceODECollisionLoggerSink();
   virtual void onInitIFaceODE();
   virtual void onCollisionWithSource( unsigned int physicsIterationCount );

   /**
      Used to record collision momentums and forces.
      \Return A pointer to this WO's collisionMap.
   */
   std::map<int, float>* getCollisionMap() { return &this->collisionMap; }
protected:
   ///collision Number, Velocity... Used to compute Force of many collisions of this WO.
   std::map<int, float> collisionMap;

};

/** \} */

} //namespace Aftr
#endif

