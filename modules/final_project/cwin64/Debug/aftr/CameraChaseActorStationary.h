#pragma once

#include "Camera.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is CHASEACTORLOOK2.
*/
class CameraChaseActorStationary : public Camera
{
public:
   CameraChaseActorStationary( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorStationary();

   CameraChaseActorStationary() = delete;
   CameraChaseActorStationary( const CameraChaseActorStationary& toCopy ) = delete;
   CameraChaseActorStationary& operator=( CameraChaseActorStationary& toAssign ) = delete;
   CameraChaseActorStationary& operator=( CameraChaseActorStationary&& toMove ) = delete;
   
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startCameraBehavior();

protected:

};


} //namespace Aftr
