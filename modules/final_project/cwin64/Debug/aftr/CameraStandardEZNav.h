#pragma once

#include "CameraStandard.h"

namespace Aftr
{

class CameraStandardEZNav : public CameraStandard
{
public:
   CameraStandardEZNav( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraStandardEZNav();

   CameraStandardEZNav() = delete;
   CameraStandardEZNav( const CameraStandardEZNav& toCopy ) = delete;
   CameraStandardEZNav& operator=( CameraStandardEZNav& toAssign ) = delete;
   CameraStandardEZNav& operator=( CameraStandardEZNav&& toMove ) = delete;

   virtual void update();

   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void moveInLookDirection();
   virtual void moveOppositeLookDirection();
   virtual void moveLeft(); ///< Pans camera to the 'left' (along camera's local +y axis)
   virtual void moveRight(); ///< Pans camera to the 'right' (along camera's local -y axis)
   virtual void setCameraVelocityMultiplier( float camVelMultiplier ); ///< Multiplier must be greater than zero

protected:

   float wheelButtonVelocityScalar;
   int wheelScrollCounter;
};

} //namespace Aftr

