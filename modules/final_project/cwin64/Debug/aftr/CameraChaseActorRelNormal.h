#pragma once

#include "Camera.h"

namespace Aftr
{

/**
   The camera instantiated when CAM_CHASE_TYPE is CHASEACTORLOOK3.
*/
class CameraChaseActorRelNormal : public Camera
{
public:
   CameraChaseActorRelNormal( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorRelNormal();

   CameraChaseActorRelNormal() = delete;
   CameraChaseActorRelNormal( const CameraChaseActorRelNormal& toCopy ) = delete;
   CameraChaseActorRelNormal& operator=( CameraChaseActorRelNormal& toAssign ) = delete;
   CameraChaseActorRelNormal& operator=( CameraChaseActorRelNormal&& toMove ) = delete;

   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startCameraBehavior();

   /// Call this after this camera's start behavior has begun (after an actor is currently)
   /// being chased. This will set the offset in front (positive) / behind (negative )the 
   /// actor to the in passed value.
   virtual void setCameraOffsetFromParent( float distance );

protected:

   float offsetFromParent = 1.0f;
   Vector relOffsetFromParentVec = { -5.0f, 0, 0 };
};


} //namespace Aftr
