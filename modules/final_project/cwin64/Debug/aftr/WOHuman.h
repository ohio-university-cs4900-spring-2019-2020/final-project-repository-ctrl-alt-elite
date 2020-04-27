#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOBoundingShell.h"
#include "IFaceODERayCast.h"

struct Mix_Chunk; //Non-namespaced forward declarations

namespace Aftr
{

class Animation;
class WOBodyPart;
class WOForceThrusterDepricated;

/** 
   \class WOHuman
   \author Scott Nykl
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

   \{
*/
class WOHuman : public WOBoundingShell, public IFaceODERayCast
{
public:

   /**
      WOHuman constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOHuman.
      \see WOBoundingShell
   */
   static WOHuman* New( const Vector& lxlylz, float mass );

   /**
      Destructor of WOHuman. Only directly deletes the animations; everything else is deleted
      by the implicit call to WO's destructor.
   */
   virtual ~WOHuman();

   //User Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   virtual void onMouseDownSelection( const SDL_MouseButtonEvent& e );
   //-----------------------------------

   virtual void onPhysicsEngineTick();
   virtual void ODEinitializeInODE();
   virtual void handleRayCollision( const dContact* contact, const dSurfaceParameters* surface );
   virtual void render( const Camera& cam ); ///Overloaded to allow optional drawing of the 'leg' Ray of the WOHuman
   virtual void initODESurface();

   /** Starts the walk animation and stops any other animation from running*/
   virtual void startWalking();
   /**Stops the walk animation, resetting the currentAnimation to none*/
   virtual void stopWalking();

   //makes all the "human" parts of the human visible
   void makeImportantPartsVisible();

   dGeomID odeRayGeomID; /// dGeomID of the WOHuman's 'leg' Ray
   bool rayIsDrawn;      /// if true, will render the WOHuman's 'leg' Ray
   float weight; ///precomputation of mass * gravity. Used for efficiency reasons in the raycast callback method.

protected:
   WOHuman( float mass );
   virtual void onCreate( const Vector& lxlylz, float mass );

   virtual void createThrusters(); ///creates the three thrusters to move/orient the WOHuman
   
   /** Constructs the human piece by piece and places them into the world connected to the human in the proper orientation*/
   virtual void constructHuman();

   virtual void loadVoices();

   void standHumanUpright();

   bool pushingFrontBackArrow;      ///used by OnKeyDown method
	bool pushingLeftRightArrow;      ///used by OnKeyDown method

   float rayLength; /// length of WOHuman's 'leg' Ray
   Vector rayDir; /// direction in which WOHuman's 'leg' Ray extends (usually straight down (0,0,-1))
   Vector rayRender; ///always equal to rayDir * rayLength... Used for efficiency reasons.

   /** The thrusters used to move the human around */
   WOForceThrusterDepricated *leftThrust, *rightThrust, *centerThrust;

   /** The body parts of the human world object, each piece represents a part of the human*/
   WOBodyPart  * torso, * head, * waist, 
               * l_upper_arm, * l_lower_arm, * r_upper_arm, * r_lower_arm, 
               * l_upper_leg, * l_lower_leg, * r_upper_leg, * r_lower_leg;

   /** The animation object for the walking animation*/
   Animation* walkAnimation;
   
   /**The animation when the human is just standing*/
   Animation* standAnimation;

   /** The walking animation is running (true) or not (false)*/
   bool isWalking;

   unsigned int uprightResetTimer;

   size_t pokeVoiceIndex;
   #ifdef AFTR_CONFIG_USE_SDL_MIXER
      std::vector< Mix_Chunk* > pokeVoices;
   #endif
};

/** \} */

} //namespace Aftr

#endif
