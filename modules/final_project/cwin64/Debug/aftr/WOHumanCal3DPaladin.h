#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_CAL3D
#ifdef AFTR_CONFIG_USE_ODE

#include "WOHumanCal3D.h"

namespace Aftr
{

/** 
   \class WOHumanCal3D
   \author Scott Nykl and Mitchell Leitch
   \brief A human. This human can walk around a world and collide with all other WOs (excluding WO).
   This is one of the most complex objects currently within the engine; hence, I've been verbose with
   the documentation so a user can figure out the structure if he/she decides to make a similarily 
   complex object.

   The human consists of two parts - the graphical model and the ODE physics model. The graphical model
   is a hiearchy of WO objects that are wrapped up inside of a WOBoundingShell. The WOBoundingShell
   is essentially the ODE Bounding box that is used for physics collisions. Using this layout enables the human
   to have many different associated animations without making collision/physics any more complicated.

   For movement, the WOHuman implements the IFaceODERayCast interface. This interface defines the human's legs.
   That is, a ray is cast down from the bottom of the WOBoundingShell towards the ground. If the ray is within a
   certain distance to the ground (the length of the legs) then an upward force is exerted. To actually move the
   WOHuman around the world, the three WOForceThrusters are used. One on each side of the WOHuman to enable
   'turning' and one at the center of the WOHuman to enable forward/backward movement. These thrusters are
   enabled/disabled by code inside of the WOHuman's onKeyDown/onKeyUp methods.

   From a graphical perspective, the WOHuman is a hierachy of WO objects (torse, head, arm, legs) that 
   are connected together via WOGJoint objects. Because WOGJoint objects can be animated, the human, itself
   becomes capable of performing 'walking' animations or any other desired animation.

   From a physics perspective, the WOHuman is an ODE Box (WOBoundingShell) with a Ray that is cast from the
   bottom of that box towards the ground. Also, three thrusters are located about the WOHuman to actually
   'propel' the WOHuman around the world.

   This can all be seen by setting the visibility of the WOBoundingShell to true and setting the
   WOHuman->rayIsDrawn to true.

   The model of this human has more body parts and is based off of the new model

   \{
*/

class WOHumanCal3DPaladin : public WOHumanCal3D
{

public:

   /**
      WOHumanCal3D constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOHuman.
      \see WOBoundingShell
   */
   static WOHumanCal3DPaladin* New( const Vector& lxlylz, float mass );

   virtual ~WOHumanCal3DPaladin();

   virtual void render( const Camera& cam );
   virtual void startWalking();
   virtual void stopWalking();

protected:
   WOHumanCal3DPaladin( float mass );

   virtual void constructHuman();
   virtual void createThrusters();

};

/** \} */

} //namespace Aftr
#endif //AFTR_CONFIG_USE_CAL3D
#endif //AFTR_CONFIG_USE_ODE
