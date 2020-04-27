#pragma once

#include "CameraLockedGlobal.h"
#include "Vector.h"

namespace Aftr
{
   class CameraLockedRelative : public CameraLockedGlobal
   {
   public:
      CameraLockedRelative( GLView* view, HandlerMouseState* handler, const Vector& offset );
      virtual ~CameraLockedRelative(){}

      CameraLockedRelative() = delete;
      CameraLockedRelative( const CameraLockedRelative& toCopy ) = delete;
      CameraLockedRelative& operator=( CameraLockedRelative& toAssign ) = delete;
      CameraLockedRelative& operator=( CameraLockedRelative&& toMove ) = delete;

      virtual void update();
   protected:
     
   };
}

