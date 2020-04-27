#pragma once

#include "WOPointSet.h"

namespace Aftr
{

class Camera;

class WOPointSetRandom : public WOPointSet
{
public:
   static WOPointSetRandom* New( const Vector& lxlylz, unsigned int numPoints, Camera** camPtrPtr );
   WOPointSetRandom* getCopyOfThisPointSet();
   virtual ~WOPointSetRandom();

   friend class MGLPointSetRandom; ///< Let the MGL for this WO access protected data
protected:
   WOPointSetRandom( const Vector& lxlylz, unsigned int numPoints, Camera** camPtrPtr );
   virtual void onCreate();

   Vector lxlylz; ///< Voxel extents for this rectangular random point set
   unsigned int numPoints; ///< Number of random points to generate within this voxel
};

} //namespace Aftr

