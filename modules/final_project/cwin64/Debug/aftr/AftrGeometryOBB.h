#pragma once

#include "Vector.h"

namespace Aftr
{

/**
   Small representation of an Arbitrarily Oriented Bounding Box, used by the
   intesection functions in AftrUtility. Designed for computational
   efficiency.
*/
class AftrGeometryOBB
{
public:
   AftrGeometryOBB( const Vector& centerPos, const Vector& LxLyLz, const Vector& xdir, const Vector& ydir, const Vector& zdir );
   virtual ~AftrGeometryOBB();
   std::string toString() const;

   /**
      Computes the current transformed verts of this OBB centered about the OBB's centerPos.
      The verts are organized as follows:
      points[0] = x + y + z;//+++
      points[1] = x + y - z;//++-
      points[2] = x - y + z;//+-+
      points[3] = x - y - z;//+--
      points[4] = y + z - x;//-++
      points[5] = y - z - x;//-+-
      points[6] = z - x - y;//--+
      points[7] = (x * -1) - y - z;//---
      Where x,y, and z are the oriented half lengths of the OBB.
   */
   void getCurrentTransformedVerts( Vector points[8] ) const;
   Vector centerPos; ///< Center point of this OBB
   Vector lxlylz; ///< Half lengths of this OBB in the X,Y, and Z dimensions, respectively.
   Vector orient[3]; ///< Relative X direction, relative Y direction, and relative Z direction, respectively.

};

} //namespace Aftr

