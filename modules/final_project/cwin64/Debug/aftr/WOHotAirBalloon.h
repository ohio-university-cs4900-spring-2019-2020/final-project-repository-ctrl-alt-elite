#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"

namespace Aftr
{
   class WOBuoyancyFluid;
   class WOODE;

class WOHotAirBalloon : public WOODE
{

public:

   /**The constructor for the hot air balloon*/
   static WOHotAirBalloon* New( WOBuoyancyFluid* air, const std::string& forceFile );

   /**Destructor for the hot air balloon*/
   virtual ~WOHotAirBalloon();

   virtual void onPhysicsEngineTick();
   /**Constructs the human and positions all the objects in the proper location*/
   void constructBalloon();

   /**Creates the buoys for the hot air balloon so it will float in the air*/
   void constructBuoys();

   /**Overloaded ode initialize to set up all of the joints and thrusters for the hot air balloon*/
   virtual void ODEinitializeInODE();

   /**Overloaded on key down for the hot air balloon*/
   virtual void onKeyDown(const SDL_KeyboardEvent& key);

   /**Overloaded on key up for the hot air balloon*/
   virtual void onKeyUp(const SDL_KeyboardEvent& key);

   /**overloaded update forces and joints for the hot air balloon*/
   virtual void ODEupdateForcesAndJoints();

protected:

   WOHotAirBalloon(WOBuoyancyFluid* air, std::string forceFile );
   virtual void onCreate( const std::string& modelFileName );

   /**Pointer to the torch object so that it can be ignited to show fire*/
   WO* torch;
   /**The WO parts of this object ie pipefl = the front left pipe, pipebr = the back right pipe.
      The basket will hold the human when on the balloon.*/
   WO* pipefl;
   WO* pipefr;
   WO* pipebl;
   WO* pipebr;
   WOODE* basket;

   /**The fluid (air) that the hot air balloon will float through*/
   WOBuoyancyFluid* air;

   /**True if the flame is running to add more heat into the balloon to make it rise*/
   bool flameOn;

   /**The path to the force file defining the location of the buoys and thrusters*/
   std::string forcePath;

};

} //namespace Aftr


#endif
