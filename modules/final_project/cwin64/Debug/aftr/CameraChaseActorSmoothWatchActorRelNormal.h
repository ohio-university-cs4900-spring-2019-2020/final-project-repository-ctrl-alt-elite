#pragma once

#include "CameraChaseActorSmoothWatchActor.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is CHASEACTORLOOK5.
*/
class CameraChaseActorSmoothWatchActorRelNormal : public CameraChaseActorSmoothWatchActor
{
public:
   CameraChaseActorSmoothWatchActorRelNormal( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorSmoothWatchActorRelNormal();

   CameraChaseActorSmoothWatchActorRelNormal() = delete;
   CameraChaseActorSmoothWatchActorRelNormal( const CameraChaseActorSmoothWatchActorRelNormal& toCopy ) = delete;
   CameraChaseActorSmoothWatchActorRelNormal& operator=( CameraChaseActorSmoothWatchActorRelNormal& toAssign ) = delete;
   CameraChaseActorSmoothWatchActorRelNormal& operator=( CameraChaseActorSmoothWatchActorRelNormal&& toMove ) = delete;
   
   //virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   //virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   //virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   //virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   //virtual void startCameraBehavior();

protected:

};



} //namespace Aftr

