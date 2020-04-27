#pragma once

#include "MGL.h"
#include "ManagerTexture.h"
#include "Vector.h"

namespace Aftr
{

class MGLBoundingShell : public MGL
{
public:
   static MGLBoundingShell* New( WO* parentWO, const Vector& lxlylz );
   virtual ~MGLBoundingShell(); 
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

protected:
   virtual void onCreate();
   MGLBoundingShell( WO* parentWO, Vector lxlylz );
   //void generateVerts(); //populate the verts

   //Vector lxlylz;
   //float xp,yp,zp,xn,yn,zn; ///verts pos x, pos y, pos z, neg x, neg y, neg z, respectively

};


}  //namespace Aftr

