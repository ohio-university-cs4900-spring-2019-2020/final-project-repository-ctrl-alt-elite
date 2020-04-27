#pragma once

#include "Vector.h"

namespace Aftr
{

class AftrGeometryRayVsFace
{
public:
   AftrGeometryRayVsFace( Vector a, Vector b, Vector c, Vector n, 
                             Vector ta, Vector tb, Vector tc,
                             unsigned int compIdxA, unsigned int compIdxB, unsigned int compIdxC );

   AftrGeometryRayVsFace( Vector a, Vector b, Vector c, Vector n );

   AftrGeometryRayVsFace( Vector a, Vector b, Vector c, Vector n, 
                             unsigned int compIdxA, unsigned int compIdxB, unsigned int compIdxC );
   
   AftrGeometryRayVsFace( unsigned int compIdxA, unsigned int compIdxB, unsigned int compIdxC );

   AftrGeometryRayVsFace();

   ~AftrGeometryRayVsFace();

   Vector computeBaryCentricCoefficientsGivenFaceVerticesAndContactPt();

   std::string toString() const;

   Vector a; Vector b; Vector c; ///< Vertex a,b,c, counter clockwise winding order of the hit face
   Vector n; ///< Normal vector of the hit face
   bool hasValidTangentData; ///< Set to true upon construction if Tangents are passed in
   Vector ta; Vector tb; Vector tc; ///< Tangent Vector, if available, corresponding to vertex a,b,c, respectively

   bool hasValidContactPt; ///< User must set to true when populating the contact point
   Vector contactPt; ///< User settable contact point. This class doesn't compute the contact point, just stores it.
                     ///< By convention, this contactPt should be specified in object/model space (local model space).
                     ///< The computation is typically done within the octree and stored/return via this class.

   unsigned int compIdxA; ///< Index into the model's composite index list which corresponds to Vector a
   unsigned int compIdxB; ///< Index into the model's composite index list which corresponds to Vector b
   unsigned int compIdxC; ///< Index into the model's composite index list which corresponds to Vector c
};

} //namespace Aftr

