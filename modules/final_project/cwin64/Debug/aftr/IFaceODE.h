#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "IFace.h"
#include <vector>

namespace Aftr
{

class IFaceODE : public virtual IFace
{
public:
   IFaceODE( WO* woUsingThisInterface );
   virtual ~IFaceODE();

   /**
      User must overload this method and initialize any data this interface manages.
      Ensure the user sets the interface's IFaceODE::woUsingThisInterface equal to
      the in passed WO* woUsingThisInterface. This ensures the user will have access
      to the associated WO which implements this interface inside of this interface's
      callbacks from within the physics engine. If the user does not set this, nothing
      bad will happen, except the user may not have access to needed data when the
      corresponding physics callback is invoked. If this is not an issue, then the
      WO* can remain unused.

      Please reference IFaceODECollisionLoggerSink or IFaceODERayCast or 
      IFaceODECollisionSensor.
   */
   virtual void onInitIFaceODE() = 0;

   static std::vector< IFaceODE* >* getIFaceODEMemberList();
protected:
   static std::vector< IFaceODE* > IFaceODEMemberList;
};

} //namespace Aftr

#endif
