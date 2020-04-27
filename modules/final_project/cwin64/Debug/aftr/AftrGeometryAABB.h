#pragma once

#include "Vector.h"

namespace Aftr
{

/**
   Small representation of an Axis Aligned Bounding Box, used by the
   intesection functions in AftrUtility. Designed for computational
   efficiency.
*/
class AftrGeometryAABB
{
public:
   AftrGeometryAABB( const Vector& centerPos, const Vector& LxLyLz );
   virtual ~AftrGeometryAABB();
   std::string toString() const;
   Vector centerPos; ///< Center point of this AABB
   Vector lxlylz; ///< Half lengths of this AABB in the X,Y, and Z dimensions, respectively.

};

} //namespace Aftr

