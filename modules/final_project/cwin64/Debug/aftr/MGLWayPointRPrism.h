#pragma once

#include "MGLWayPointAbstract.h"

namespace Aftr
{

   class IndexedGeometryRectangularPrism;

class MGLWayPointRPrism : public MGLWayPointAbstract
{
public:
  MGLWayPointRPrism( WOWayPointAbstract* parent ///parent WOWayPoint that uses this model
				  );
  virtual ~MGLWayPointRPrism();
  virtual void renderMe( const Camera& cam );
protected:
   IndexedGeometryRectangularPrism* prism;
  
};


}  //namespace Aftr

