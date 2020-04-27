#pragma once

#include "Camera.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is CHASEACTORLOOK.
*/
class CameraChaseActorAbsNormal: public Camera
{
public:
   CameraChaseActorAbsNormal( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorAbsNormal();

   CameraChaseActorAbsNormal() = delete;
   CameraChaseActorAbsNormal( const CameraChaseActorAbsNormal& toCopy ) = delete;
   CameraChaseActorAbsNormal& operator=( CameraChaseActorAbsNormal& toAssign ) = delete;
   CameraChaseActorAbsNormal& operator=( CameraChaseActorAbsNormal&& toMove ) = delete;
   
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startCameraBehavior();

protected:

};


} //namespace Aftr
