#pragma once

#include "Camera.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is CHASEACTORLOOK2.
*/
class CameraChaseActorSmooth : public Camera
{
public:
   CameraChaseActorSmooth( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorSmooth();

   CameraChaseActorSmooth() = delete;
   CameraChaseActorSmooth( const CameraChaseActorSmooth& toCopy ) = delete;
   CameraChaseActorSmooth& operator=( CameraChaseActorSmooth& toAssign ) = delete;
   CameraChaseActorSmooth& operator=( CameraChaseActorSmooth&& toMove ) = delete;

   /**
      Each update, this chase mode computes the distance between where the camera
      currently is and where the actor is. This distance is multiplied by this 
      factional scalar to determine the distance the camera will move towards
      the actor this update. The default value is 0.03f; that is, each update,
      The camera moves 3% closer to the actor. The closer to 0 this value is, the
      slower the camera will approach the actor. The closer to 1 this value is,
      the faster the camera will approach the actor.
   */
   virtual void setChaseModeVelocityRatio( float percentOfDistanceToApproachActor );
   virtual float getChaseModeVelocityRatio();
   
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startCameraBehavior();

protected:

   Vector chaseModeCurCamPos;
   float chaseModeVelocityRatio;

};


} //namespace Aftr
