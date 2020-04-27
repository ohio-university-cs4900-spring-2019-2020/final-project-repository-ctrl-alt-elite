#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"
#include "IFaceODERayCast.h"

namespace Aftr
{

class WOForceThruster;
class WOGhostLidar;

/** 
   \class WOHelicopterApache
   \author Scott Nykl
   \brief A human. This human can walk around a world and collide with all other WOs (excluding WO).
   This is one of the most complex objects currently within the engine; hence, I've been verbose with
   the documentation so a user can figure out the structure if he/she decides to make a similarily 
   complex object.

   The human consists of two parts - the graphical model and the ODE physics model. The graphical model
   is a hiearchy of WO objects that are wrapped up inside of a WOBoundingShell. The WOBoundingShell
   is essentially the ODE Bounding box that is used for physics collisions. Using this layout enables the human
   to have many different associated animations without making collision/physics any more complicated.

   For movement, the WOHelicopterApache implements the IFaceODERayCast interface. This interface defines the human's legs.
   That is, a ray is cast down from the bottom of the WOBoundingShell towards the ground. If the ray is within a
   certain distance to the ground (the length of the legs) then an upward force is exerted. To actually move the
   WOHelicopterApache around the world, the three WOForceThrusters are used. One on each side of the WOHelicopterApache to enable
   'turning' and one at the center of the WOHelicopterApache to enable forward/backward movement. These thrusters are
   enabled/disabled by code inside of the WOHelicopterApache's onKeyDown/onKeyUp methods.

   From a graphical perspective, the WOHelicopterApache is a hierachy of WO objects (torse, head, arm, legs) that 
   are connected together via WOGJoint objects. Because WOGJoint objects can be animated, the human, itself
   becomes capable of performing 'walking' animations or any other desired animation.

   From a physics perspective, the WOHelicopterApache is an ODE Box (WOBoundingShell) with a Ray that is cast from the
   bottom of that box towards the ground. Also, three thrusters are located about the WOHelicopterApache to actually
   'propel' the WOHelicopterApache around the world.

   This can all be seen by setting the visibility of the WOBoundingShell to true and setting the
   WOHelicopterApache->rayIsDrawn to true.

   \{
*/
class WOHelicopterApache : public virtual WOODE, public virtual IFaceODERayCast
{
public:

   /**
      WOHelicopterApache constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOHelicopterApache.
      \see WOBoundingShell
   */
   static WOHelicopterApache* New( const std::string& modelFileName, Vector scale = Vector( 1.0, 1.0, 1.0 ), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   static WOHelicopterApache* New( Vector scale = Vector( 1.0, 1.0, 1.0 ) );


   /**
      Destructor of WOHelicopterApache. Only directly deletes the animations; everything else is deleted
      by the implicit call to WO's destructor.
   */
   virtual ~WOHelicopterApache();

   //User Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   
   void setBladVelocityMain( float radPerSec );
   void setBladeVelocityRear( float radPerSec );
   float getBladeVelocityMain() { return this->bladeMainVel; }
   float getBladeVelocityRear() { return this->bladeRearVel; }

   bool setLidarEnabled();
   void setLidarEnabled( bool isEnabled );
   void setLidarPerformScan( bool performScan );
   WOGhostLidar* getLidar() { return this->lidar; }

   virtual void onUpdateWO();
   virtual void initODESurface();
   virtual void ODEinitializeInODE();
   virtual void handleRayCollision( const dContact* contact, const dSurfaceParameters* surface );
   virtual void ODEupdateToNewPositionOrientation();
   virtual void ODEupdateForcesAndJoints();
   virtual void render( const Camera& cam );

protected:
   virtual void onCreate(const std::string& modelFileName, const Vector& scale, MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO);
   WOHelicopterApache();

   void constructor();
   /** creates the three thrusters to move/orient the WOHelicopterApache */
   void createThrusters();
   /** Constructs the human piece by piece and places them into the world connected to the human in the proper orientation*/
   void constructHelicopter();
   /** Creates ray casted from belly of chopper towards ground for altitude control*/
   void createRayCast();
   void loadSounds();
   void orientApacheUpright();

   bool pushingFrontBackArrow;      ///used by OnKeyDown method
	bool pushingLeftRightArrow;      ///used by OnKeyDown method
   bool pushingThrustUpDownArrow;   ///used by OnKeyDown method
   bool landedOnGround; ///true if ray intersects terrain; false, otherwise


   /** The thrusters used to move the human around */
   WOForceThruster *leftThrust, *rightThrust, *centerThrust, *upDownThrust;

   /** Each piece represents a part of the Helicopter*/
   WO* bladeMain;
   WO* bladeRear;
   WOGhostLidar* lidar;


   float bladeMainVel;
   float bladeRearVel;

   //------ Ray casting variables
   /// length of WOHuman's 'leg' Ray
   float initialRayLength;
   float rayLength;   
   /// direction in which WOHuman's 'leg' Ray extends (usually straight down (0,0,-1))
   Vector rayDir;
   ///always equal to rayDir * rayLength... Used for efficiency reasons.
   dGeomID odeRayGeomID; /// dGeomID of the WOHuman's 'leg' Ray
   bool rayIsDrawn;      /// if true, will render the WOHuman's 'leg' Ray
   //------ 


   unsigned int uprightResetTimer;
};

/** \} */

} //namespace Aftr

#endif
