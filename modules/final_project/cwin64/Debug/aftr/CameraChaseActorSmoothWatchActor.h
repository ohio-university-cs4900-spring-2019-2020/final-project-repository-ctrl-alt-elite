#pragma once

#include "CameraChaseActorSmooth.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is CHASEACTORLOOK4.
*/
class CameraChaseActorSmoothWatchActor : public CameraChaseActorSmooth
{
public:
   CameraChaseActorSmoothWatchActor( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorSmoothWatchActor();

   CameraChaseActorSmoothWatchActor() = delete;
   CameraChaseActorSmoothWatchActor( const CameraChaseActorSmoothWatchActor& toCopy ) = delete;
   CameraChaseActorSmoothWatchActor& operator=( CameraChaseActorSmoothWatchActor& toAssign ) = delete;
   CameraChaseActorSmoothWatchActor& operator=( CameraChaseActorSmoothWatchActor&& toMove ) = delete;
   
   //virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   //virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   //virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   //virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   //virtual void startCameraBehavior();

protected:

   //Vector chaseModeCurCamPos;
   //float chaseModeVelocityRatio;

};


} //namespace Aftr
