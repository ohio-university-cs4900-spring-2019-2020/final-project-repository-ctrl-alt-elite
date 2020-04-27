#pragma once

#include "WO.h"

namespace Aftr
{

   class Camera;
   class WorldList;
   class AftrFrameBufferObject;

class WOCameraSink : public WO
{
public:
   static WOCameraSink* New(Camera** source, WorldList* lst, unsigned int timer, float width, float height);
   
   virtual ~WOCameraSink();
   virtual void onPhysicsEngineTick();
   AftrFrameBufferObject* getFbo() { return fbo; }
   virtual void onClientSideUpdateWO();
protected:
   virtual void onCreate(float width, float height);
   WOCameraSink(Camera** source, WorldList* lst, unsigned int timer);
   unsigned int internalTimer;
   unsigned int timer;
   AftrFrameBufferObject* fbo;
   Camera** source;
   WorldList* lst;
};

}

