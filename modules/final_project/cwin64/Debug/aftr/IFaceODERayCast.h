#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "IFaceODE.h"

struct dContact;
struct dSurfaceParameters;

namespace Aftr
{

/** \class IFaceODERayCast
    \brief An interface used by any WO that casts an ODE Ray.
           This interface provides a way for the physics engine
           to pass important ray collision data to the WO level
           where the user can use the collision data as he wishes.

    \{
*/
class IFaceODERayCast : public virtual IFaceODE
{
public:
   IFaceODERayCast( WO* woUsingThisInterface );
   virtual ~IFaceODERayCast();
   virtual void onInitIFaceODE();
   virtual void handleRayCollision( const dContact* contact, const dSurfaceParameters* surface ) = 0;
private:
};

/** \} */

} //namespace Aftr

#endif
