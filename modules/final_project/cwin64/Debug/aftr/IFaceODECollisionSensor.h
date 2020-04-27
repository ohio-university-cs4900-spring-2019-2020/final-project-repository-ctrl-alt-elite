#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "IFaceODE.h"
#include "AftrGlobals.h"
#include "AftrODEIncludes.h"

struct dContact;

namespace Aftr
{

/** \class IFaceODECollisionSensor
    \brief An interface used by any WO that wants to have a callback
    invoked whenever this object's bounding box collides with with any
    other ODE geometry.
    
    This interface is useful for example, when a WO (or sublcass)
    needs to know if something "collided" with it. This is because WO objects
    do not have corresponding physics bodies and cannot therefore collide.
    The handleSensorCollision
    method is invoked when any object with corresponding ODE Geometry collides
    with the bounding box of this model.

    \{
*/
class IFaceODECollisionSensor : public virtual IFaceODE
{
public:

   IFaceODECollisionSensor( WO* woUsingThisInterface );
   virtual ~IFaceODECollisionSensor();

   /**
      This method is invoked inside the physics engine at the same time as WO::ODEinitializeInODE().
      A dGeom will be created based on the graphical model's bounding box. This geom will be used only
      to sense collisions. No physical forces can be directly applied to this geom; that is, the geom
      will trigger a callback to handleSensorCollision(), but ODE objects will simply pass through this
      sensor Geom as though nothing was there.
   */
   virtual void onInitIFaceODE( WO* woBeingMonitoredForCollisions );

   /**
      This method is invoked when the graphical model's bounding box collides with any other Geom in the simulation
      (except for its own parent). The object that collides with this sensor will behave exactly as though the sensor
      never existed; that is, the colliding object will simply pass straight through the sensor. This sensor is
      basically a phantom; nothing can touch it, but it knows when something touches it.
   */
   virtual void handleSensorCollision( WO* colliderWO );

   /**
      This method MUST be invoked in order to synchronize the ODE Geom used by this sensor with the
      latest position and orientation of the graphical model. It is recommended that this call be
      added to the end of the corresponding WO::ODEupdateToNewPositionOrientation(). 
      So simply overload the current ODEupdateToNewPositionOrientation() method to call the parent
      ODEupdateToNewPositionOrientation() via MyParentWO::ODEupdateToNewPositionOrientation(). Finally
      add the call this->IFaceODECollisionSensorUpdateToNewPositionOrientation().

      The end result is a new two line ODEupdateToNewPositionOrientation() which updates this interface
      each time the engine calls ODEupdateToNewPositionOrientation on all WOs.

      An example is (WOGhostScud directly inherits from WO):
         void WOGhostScud::ODEupdateToNewPositionOrientation()
         {
            WO::ODEupdateToNewPositionOrientation();
            this->IFaceODECollisionSensorUpdateToNewPositionOrientation();   
         }
   */
   virtual void IFaceODECollisionSensorUpdateToNewPositionOrientation();

   dGeomID IFaceODECollisionSensorGeomID;
   dBodyID IFaceODECollisionSensorBodyID;

};

/** \} */

} //namespace Aftr

#endif
