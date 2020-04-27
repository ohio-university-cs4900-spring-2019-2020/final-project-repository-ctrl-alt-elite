#pragma once

#include "MGL.h"

namespace Aftr
{

   class WOWayPointAbstract;
  
class MGLWayPointAbstract : public MGL
{
public:

  MGLWayPointAbstract( WOWayPointAbstract* parent ///< parent WOWayPoint that uses this model
				  );
   virtual ~MGLWayPointAbstract();

   ///use this function to render the waypoint (typically only needed for debug purposes)
   virtual void renderMe( const Camera& cam ) = 0;
   virtual void render( const Camera& cam );
   virtual void renderSelection(GLubyte red, GLubyte green, GLubyte blue);
   
protected:	
	WOWayPointAbstract* parent;
	
};

}  //namespace Aftr

