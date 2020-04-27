#pragma once

#include "AftrOpenGLIncludes.h"

namespace Aftr
{

class Camera;

class Particle
{
public:
   virtual void render( const Camera& cam ) = 0;
   virtual bool update( unsigned int u ) = 0;
protected:

};
}

