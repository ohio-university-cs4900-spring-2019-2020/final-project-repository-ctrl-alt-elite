#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOStatic.h"

namespace Aftr
{

class WOGhostScud;

/** 
   \class WOFixedScudLauncher
   \author Scott Nykl
   \brief A Fixed-position scud launcher.

   \{
*/
class WOFixedScudLauncher : public WOStatic
{
public:

   /**
      WOFixedScudLauncher constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOFixedScudLauncher.
      \see WOBoundingShell
   */
   static WOFixedScudLauncher* New( const std::string& modelFileName, const std::string& missleModelFileName, Vector scale = Vector( 1.0, 1.0, 1.0 ), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   static WOFixedScudLauncher* New( Vector scale = Vector( 1.0, 1.0, 1.0 ), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );

   /**
      Destructor of WOFixedScudLauncher. Only directly deletes the animations; everything else is deleted
      by the implicit call to WO's destructor.
   */
   virtual ~WOFixedScudLauncher();

   //User Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );

   virtual void ODEupdateForcesAndJoints();
   virtual void ODEinitializeInODE();

   float getTrajAzimuth() { return this->trajAzimuth; }
   float getTrajElevation() { return this->trajElevation; }
   float getTrajInitialVel() { return this->trajInitialVel; }
   void reloadScud();

protected:
   WOFixedScudLauncher();
   virtual void onCreate( const std::string& modelFileName, const std::string& missleModelFileName, Vector scale = Vector( 1.0, 1.0, 1.0 ), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   virtual void onCreate( Vector scale = Vector( 1.0f, 1.0f,1.0f ), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );

   void launchScud();

   void constructor();
   void createScud( std::string* missleModelFileName = NULL );
   void updateTrajectory( float deltaTheta, float deltaPhi );
   void updateAzimuthElevation();

   bool firstUpdate;
   bool scudInFlight;

   float trajAzimuth;
   float trajElevation;
   float trajInitialVel;

   WOGhostScud* scud; //make this a WOGhostScud that uses IFaceODERayCast for collision checks
};

/** \} */

} //namespace Aftr

#endif
