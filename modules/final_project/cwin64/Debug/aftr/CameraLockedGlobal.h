#pragma once

#include "Camera.h"
#include "Vector.h"

namespace Aftr
{
   class CameraLockedGlobal : public Camera
   {
   public:
      CameraLockedGlobal( GLView* view, HandlerMouseState* handler, const Vector& offset );
      virtual ~CameraLockedGlobal(){}

      CameraLockedGlobal() = delete;
      CameraLockedGlobal( const CameraLockedGlobal& toCopy ) = delete;
      CameraLockedGlobal& operator=( CameraLockedGlobal& toAssign ) = delete;
      CameraLockedGlobal& operator=( CameraLockedGlobal&& toMove ) = delete;

      virtual void update();
      void setOffset(const Vector& offset) { this->offset = offset; }
   protected:
      Vector offset;
   };
}

