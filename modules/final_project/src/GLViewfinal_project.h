#pragma once

#include "GLView.h"

namespace Aftr
{
   class Camera;

/**
   \class GLViewfinal_project
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewfinal_project : public GLView
{
public:
   static GLViewfinal_project* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewfinal_project();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );


   //Object creation methods
   virtual void createNewModuleWayPoints();
   virtual void createPlayersAKModel();
   virtual void bulletFiredFromGun(WO* Shooter);
   virtual void WeaponFiring(WO* Shooter);
   std::vector<size_t> ExistingBulletIDs;
   virtual void MoveBullet(WO* Bullet);
   virtual void GenerateRandomTargetHuman(float xCoord, float yCord);

   int total_hit;

protected:
   GLViewfinal_project( const std::vector< std::string >& args );
   virtual void onCreate();   
   size_t PlayerWeaponWOIndex;
   

   //Creates the sound manager for the module:
};

/** \} */

} //namespace Aftr
