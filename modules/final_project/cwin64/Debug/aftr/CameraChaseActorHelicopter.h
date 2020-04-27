#pragma once

#include "Camera.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is HELICOPTERLOOK.
*/
class CameraChaseActorHelicopter: public Camera
{
public:
   CameraChaseActorHelicopter( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorHelicopter();

   CameraChaseActorHelicopter() = delete;
   CameraChaseActorHelicopter( const CameraChaseActorHelicopter& toCopy ) = delete;
   CameraChaseActorHelicopter& operator=( CameraChaseActorHelicopter& toAssign ) = delete;
   CameraChaseActorHelicopter& operator=( CameraChaseActorHelicopter&& toMove ) = delete;
   
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startCameraBehavior();

protected:

   float paramTime;
   float paramAngleAboveHorizon;
   float paramRadius;

};


} //namespace Aftr
