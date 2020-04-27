#pragma once

#include "MGL.h"
#include <string>
using std::string;

namespace Aftr
{

class MGLQuadStripSphere : public MGL
{

public:

   MGLQuadStripSphere( WO* parentWO, float radius, int row, int column, const string& texture, float portion);
   ~MGLQuadStripSphere();  
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   void spoofTextureIndex(int i){}
protected:
	float radius;
	int row;
	int column;	
	float portion;

	//internal structure
	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* textureCoordinates;
   GLushort* indices;
};


}  //namespace Aftr

