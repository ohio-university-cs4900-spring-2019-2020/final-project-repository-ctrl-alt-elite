#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "IFaceODE.h"
#include <map>

namespace Aftr
{

/** \class IFaceODECollisionLoggerSource
    \brief An interface used by any WO that records the velocities
    of this object after a collision.

    \{
*/
class IFaceODECollisionLoggerSource : public virtual IFaceODE
{
public:
   IFaceODECollisionLoggerSource( WO* woUsingThisInterface );
   virtual ~IFaceODECollisionLoggerSource();
   virtual void onInitIFaceODE();
};

/** \} */

} //namespace Aftr

#endif
