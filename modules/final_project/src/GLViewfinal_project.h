#pragma once

#include "GLView.h"
#include "box.h"
#include "target.h"
#include "gun.h"
#include "bullet.h"
#include <WOGUILabel.h>
#include <WOFTGLString.h>
#include <MGLFTGLString.h>

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
   virtual void createfinal_projectWayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   virtual void fire_bullet();

   Box* box1;
   Box* box2;
   Box* box3;
   Box* box4;
   Target* target1;
   Target* target2;
   Target* target3;
   Target* target4;
   Gun* gun;
   Bullet* bullet;

   //WOWayPointSpherical* wayPt;
   //WOGUILabel* testText;
   int total_hit;
   //WOGUILabel* testText = WOGUILabel::New(nullptr);

protected:
   GLViewfinal_project( const std::vector< std::string >& args );
   virtual void onCreate();   
};

/** \} */

} //namespace Aftr
