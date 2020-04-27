#pragma once

#include "Vector.h"
#include <string>
#include <vector>

namespace Aftr
{

class AftrGeometryFrustum
{
public:
   AftrGeometryFrustum();

   AftrGeometryFrustum( float aspectRatioWidthToHeight, float verticalFOVDeg,
                           float nearPlaneDist, float farPlaneDist, const Vector& lookDirection,
                           const Vector& normalDirection, const Vector& cameraPos );

   virtual ~AftrGeometryFrustum();

   /// Tests if the in passed point resides within the frustum's volume. The in passed point
   /// must reside in the same reference frame as the cameraPos passed to this frustum's constructor.
   /// Returns true iff the point resides within the volume of the frustum; false, otherwise.
   bool isInFrustum( const Vector& point ) const;
   /// Returns normal for the ith plane [0,5]. These normals point out from the interior the view frustum.
   /// top, bottom, left, right, near, far corresponding to indices 0,1,2,3,4,5, respectively.
   /// These normals are defined in World Space (not object space).
   Vector getPlaneNormal( unsigned int i ) const; ///< Returns normal for the ith plane [0,5]. These normals point into the view frustum.
   /// Returns distance from origin along normal for ith plane [0,5].
   /// top, bottom, left, right, near, far corresponding to indices 0,1,2,3,4,5, respectively.
   /// These coefficients are defined in World Space (not object space).
   float getPlaneCoef( unsigned int i ) const; ///< Returns distance from origin along normal for ith plane [0,5].
   std::string toString() const;

   const std::vector< std::pair< Vector, Vector > >& getEdges() const { return this->edges; };

protected:

   void init( float aspectRatioWidthToHeight, float verticalFOVDeg,
           float nearPlaneDist, float farPlaneDist, const Vector& lookDirection,
           const Vector& normalDirection, const Vector& cameraPos );

   Vector top;
   float topCoef;
   Vector bottom;
   float bottomCoef;
   Vector left;
   float leftCoef;
   Vector right;
   float rightCoef;
   Vector nearer;
   float nearCoef;
   Vector farther;
   float farCoef;

   std::vector< std::pair< Vector, Vector > > edges;
};

} //namespace Aftr

