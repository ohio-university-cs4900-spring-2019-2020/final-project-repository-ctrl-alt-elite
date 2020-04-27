//-------------------------------------------------
// Description: Shark world object, uses pathfinding
//              and animations to track the human when
//              he ventures to far into the water
//
// Author:  Mitchell Leitch
//-------------------------------------------------

#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOBoundingShell.h"

namespace Aftr
{

   class Animation;
   class WOOcean;
   class WOForceThrusterDepricated;
   class AICollisionWayPoint;

/**
   \class WOShark
   \author Mitchell Leitch (updated by Chad Mourning and Scott Nykl)
   \brief Shark world object that swims around and can pathfind to objects
   \{
   */

class WOShark : public WOBoundingShell
{

public:

   /**Default constructor, explicitly calls construct shark function to build the shark.
      Takes the sharkModel and passes it to the WO constructor*/
   static WOShark* New( const Vector& lxlylz, float mass, WOOcean* ocean = NULL, std::string abstractForce = "", WO* target = NULL, int behavior = 0 );

   /**Destructor for the shark, cleans up all the children (shark body parts)*/
   virtual ~WOShark();

   /**Constructs the shark positioning the body parts in the proper location*/
   void constructShark();

   virtual void ODEupdateToNewPositionOrientation();
   virtual void onPhysicsEngineTick();
   void addObsticle(AICollisionWayPoint* x){obsticles.push_back(x);}

   void setDestination(WO* x){destination = x;}

protected:
   WOShark( WOOcean* ocean, const std::string& abstractForce, WO* destination );
   virtual void onCreate( const Vector& lxlylz, float mass, int behavior );

   /**The children of the shark, all body parts that could be animated. 
      This is used to keep track of certain body parts.*/
   WO* torso;
   WO* jaw;
   WO* leftFin;
   WO* rightFin;
   WO* dorsalFin;
   WO* tail;
   WO* destination;
   std::string abstractForceFile;
   WOOcean* ocean;
   
   void setBehavior( int behavior );
   void createBuoys();
   void createThrusters();
   WOForceThrusterDepricated* leftThruster;
   WOForceThrusterDepricated* rightThruster;
   WOForceThrusterDepricated* centerThruster;

   /**This is the animation for the shark to wag his tail swimming*/
   Animation* sharkAnimation;

   //pathfinding components
   std::vector<AICollisionWayPoint*> obsticles;
   
   Vector approachDestination();
   Vector avoidObsticles();
   void updateHeading(Vector h);



};

/** \} */


} //namespace Aftr


#endif
