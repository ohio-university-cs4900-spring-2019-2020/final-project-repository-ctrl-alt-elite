#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIDepthMap : public WOGUI
{
public:
   static WOGUIDepthMap* New( WOGUI* parentWOGUI, float width, float height, Texture* depthBufferTexture );
   virtual ~WOGUIDepthMap();
   void setNearPlaneForDepthTexture( float near );
   void setFarPlaneForDepthTexture( float far );
protected:
   WOGUIDepthMap( WOGUI* parentWOGUI );
   virtual void onCreate( WOGUI* parentWOGUI, float width, float height, Texture* depthBufferTexture );
};

} //namespace Aftr

