#pragma once

#include "MGLWayPointAbstract.h"

namespace Aftr
{

   class IndexedGeometryDisc;

class MGLWayPointDisc : public MGLWayPointAbstract
{
public:
  MGLWayPointDisc( WOWayPointAbstract* parent = NULL );
   virtual ~MGLWayPointDisc();
   virtual void renderMe( const Camera& cam );
protected:	
  IndexedGeometryDisc* disc;
};

}  //namespace Aftr

