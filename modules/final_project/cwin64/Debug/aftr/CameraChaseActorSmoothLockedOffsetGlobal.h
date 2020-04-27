#pragma once

#include "Camera.h"

namespace Aftr
{
      class CameraChaseActorSmoothLockedOffsetGlobal : public Camera
{
public:
   CameraChaseActorSmoothLockedOffsetGlobal( GLView* view, HandlerMouseState* handler );
   virtual ~CameraChaseActorSmoothLockedOffsetGlobal();

   CameraChaseActorSmoothLockedOffsetGlobal() = delete;
   CameraChaseActorSmoothLockedOffsetGlobal( const CameraChaseActorSmoothLockedOffsetGlobal& toCopy ) = delete;
   CameraChaseActorSmoothLockedOffsetGlobal& operator=( CameraChaseActorSmoothLockedOffsetGlobal& toAssign ) = delete;
   CameraChaseActorSmoothLockedOffsetGlobal& operator=( CameraChaseActorSmoothLockedOffsetGlobal&& toMove ) = delete;

   void setOffset( const Vector& x );
   void setSpeed( float x ) { chaseSpeed = x; }
   virtual void update();
protected:
   Vector globalOffsetFromActor;
   float chaseSpeed;
};

}

