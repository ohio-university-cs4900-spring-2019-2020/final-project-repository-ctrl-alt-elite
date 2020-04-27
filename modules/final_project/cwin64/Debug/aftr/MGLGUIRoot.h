#pragma once

#include "MGLGUI.h"
#include "ModelMeshSkin.h"
#include "TextureData.h"

namespace Aftr
{

class IndexedGeometryQuad;
class AftrFrameBufferObject;
class Font;

class MGLGUIRoot : public MGLGUI
{
public:
   static MGLGUIRoot* New( WO* parentWO, const std::string& texture, float width, float height );
   static MGLGUIRoot* New( WO* parentWO, float width, float height );
   virtual ~MGLGUIRoot();
   virtual void render( const Camera& cam );
   virtual void updateFBOSize( int widthInPixels, int heightInPixels );
   AftrFrameBufferObject* getFBO();
   
protected:
   MGLGUIRoot( float width, float height, WO* parentWO );
   virtual void onCreate( const std::string& texture );
   virtual void onCreate();
   AftrFrameBufferObject* fbo = nullptr;
};

} //namespace Aftr

