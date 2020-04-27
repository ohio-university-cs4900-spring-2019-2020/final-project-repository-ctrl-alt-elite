#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"
#include "IFaceODERayCast.h"

namespace Aftr
{

/** 
   \class WOGhostScud
   \author Scott Nykl
   \brief A Fixed-position scud launcher.

   \{
*/
class WOGhostScud : public WOODE//, IFaceODERayCast
{
public:
   /**
      WOGhostScud constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOGhostScud.
      \see WOBoundingShell
   */
   static WOGhostScud* New( const std::string& modelFileName, Vector scale = Vector( 1.0, 1.0, 1.0 ) );
   static WOGhostScud* New( Vector scale = Vector( 1.0f, 1.0f, 1.0f ) );

   /**
      Destructor of WOGhostScud. Only directly deletes the animations; everything else is deleted
      by the implicit call to WO's destructor.
   */
   virtual ~WOGhostScud();

   virtual void render( const Camera& cam );

   //virtual void handleRayCollision( const dContact* contact, const dSurfaceParameters* surface );

   //User Input Specific
   //-----------------------------------

   virtual void ODEinitializeInODE();
   virtual void ODEupdateForcesAndJoints();

   virtual void launchScud( float initialVel );

protected:
   WOGhostScud();
   virtual void onCreate( const std::string& modelFileName, const Vector& scale );

   void constructor();
   void syncCollisionRay();
   void generateTrajectoryData( float initialVel );
   void flyScudOneTick();
   void reloadScud();

   dGeomID collisionRay; //Ray used by Scud for collision detection
   bool renderCollisionRay;
   float collisionRayLength;

   enum SCUD_STATE { AIMING, FLYING, CRASHING };
   SCUD_STATE state;

   struct TRAJECT_DATA
   {
      Vector startPos; //initial launch coord
      Vector startOrient; //initial lookDir
      Vector XYPlanProj; //Horizontal components of velocity (Mag(X,Y,0) == 1)
      float initialTheta; //vertical angle of launch (elevation)
      float initialVel; //initial launch velocity
      float initialXYVel; //X (horizontal) component of initial vel
      float initialZVel; //Y (vertical) component of initial vel
      float theta; //angle between XY Plane and scud's lookDir
      float deltaTheta; //amount theta is changed each tick
      float expFlightTime; //expected flight time in seconds
      unsigned int expNumPhysTicks; //discrete phys tick summing up to expFlightTime
      float expHorzDisp; //assuming flat terrain
      float expVertDisp; //assuming initial height was zero on flat terrain
      float maxYDisp;

      float currFlightTime; //incremented by time step interval each call to ODEupdateForcesAndJoints
      unsigned int currPhysTick; //incremented each tick
      float currCumulativeRotation; //The scud should only rotate by 2*initialTheta over its flight
      float rotPerTick;
   };

   TRAJECT_DATA data;
};

/** \} */

} //namespace Aftr

#endif
