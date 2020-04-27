#pragma once

#include "MGL.h"
#include "ManagerTexture.h"
#include "WOQuadStripSphere.h"
#include <string>
using std::string;

namespace Aftr
{
   class GLView;

class MGLParallaxSphere : public MGL
{
public:

   MGLParallaxSphere( WO* parentWO, GLView* view, float r, string t, float v );
   ~MGLParallaxSphere(); 
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );   
protected:
	GLView* glview;	
	string* tex;
	float radius;	
	float velocity;
	float rotation;
	WOQuadStripSphere* sphere;
};


}  //namespace Aftr

