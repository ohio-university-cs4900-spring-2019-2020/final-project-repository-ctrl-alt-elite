#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"


namespace Aftr
{

   class WOForceBuoy;
   class WOForceThrusterDepricated;
   class WOBuoyancyFluid;

   enum class BOAT_HULL_TYPE : unsigned char { bhTRIANGULAR = 0, bhRECTANGULAR, bhCYLINDRICAL };
   std::ostream& operator<<( std::ostream& out, const BOAT_HULL_TYPE& bht );

/**
   \author Scott Nykl
   This class represents any object that shall exhibit buoyant properties with respect
   to the assoicated water body of this buoyant object. For example, if a model of a sail
   boat is created and instianted as a new WOBoat(...), the sail boat shall remain
   buoyant with respect to the water world object that it is associated with. The buoyant
   force is calculated as a function of volume displaced by the hull of the sail boat.

   That is, true buoyancy is calculated and utilized.

   The user must specify the hull configuration type and hull dimensions in the constructor
   for this object.
   /{
*/
class WOBoat : public WOODE
{

public:
   /**
      Creates a WO with the graphical representation of the in passed VRML file 
      \param modelFileName: relative path to graphical model that shall be opened.
      \param BOAT_HULL_TYPE: 3D geometric object that approximates the boat's hull.
      \param Vector*: X component - length of hull in x-axis.
                      Y component - length of hull in y-axis.
                      Z component - length of hull in z-axis (height).
                      A copy of the data inside the Vector* is stored in this class.
      \param WOWater*: The body of "liquid" the boat shall use to compute buoyancy.
   */
   static WOBoat* New( const std::string& modelFileName, const std::string& abstractForceFileName, WOBuoyancyFluid* waterBody );

   /**
      Destructor 
   */
   virtual ~WOBoat();

   //User Keyboard Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   //-----------------------------------

   WOForceThrusterDepricated* getLeftThruster() { return this->leftThruster; }
   WOForceThrusterDepricated* getRightThruster() { return this->rightThruster; }

   

   //ODE Specific
   //-----------------------------------
   //Methods specific for integrating this WO with ODE
   //Children of this class need to overload these methods so ODE can use these WorldObjects appropriately

   /**
      Creates the ODE representation of this WO. For example, if the WO is a Sphere, then the corresponding
      ODE geom, body, and mass objects associated with that Sphere are created inside this method. This method will be used ONLY by ODE.
      Do not manually call this, otherwise ODE's state machine will become "undefined".
   */
   virtual void ODEinitializeInODE();


   /**
      This method returns a pointer to the WOWater that this
      WOBoat is associated with; ie, float in.
      \return The body of liquid associated with this WOBoat.
   */
   WOBuoyancyFluid* getAssociatedWaterBody() { return this->waterBody; }

   /**
     Makes everything about the boat visible, execept for things labeled as buoys and thrusters.
   */
   void makeOnlyHullVisible();

protected:

   WOBoat( const std::string& abstractForceFileName, WOBuoyancyFluid* waterBody );
   virtual void onCreate( const std::string& modelFileName );

   bool forward; ///used for keyboard control states
   bool left; ///used for keyboard control states
   bool pushingFrontBackArrow;      //used by OnKeyDown method
	bool pushingLeftRightArrow;      //used by OnKeyDown method

   /** Body of liquid this boat shall float in. */
   WOBuoyancyFluid* waterBody;

   /** 3D Approximation of hull configuration. */
   BOAT_HULL_TYPE hullType;

   /** Path to abstract force file containing buoyancy information for this boat */
   std::string abstractForceFileName;

   WOForceThrusterDepricated* leftThruster;
   WOForceThrusterDepricated* rightThruster;

   /**
      This method creates WOForceBuoy Objects which are responsible for
      computing and applying Buoyant forces to the Boat when it is fully
      or paritially submerged in the associated WOWater*.

      This method is temporary in that, it shall eventually be replaced with
      a "Abstract Force" file that is read in at load time. This file will contain
      the position and radii of the WOForceBuoy Objects.
   */
   virtual void createBuoys();

   
   virtual void createThrusters();

};

/**
   \}
*/

} //namespace Aftr
#endif
