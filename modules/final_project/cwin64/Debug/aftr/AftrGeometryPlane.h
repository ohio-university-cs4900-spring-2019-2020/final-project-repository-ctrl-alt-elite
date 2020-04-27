#pragma once

#include "Vector.h"
#include <string>

namespace Aftr
{
	
class AftrGeometryPlane
{
public:
   /**
      Default constructor
   */
   AftrGeometryPlane();
   /**
      Constructor taking each element
   */
   AftrGeometryPlane(float x, float y, float z, float d);
   /**
      Default destructor
   */
   virtual ~AftrGeometryPlane() {}
   /**
      Returns a Vector that is the normal of the plane
   */
   Vector getNormal() const { return Vector(x,y,z); }
   /**
      Sets the x,y,z coefficents of this plane to the in passed normal
   */
   void setNormal( const Vector& norm );
   /**
      Returns the displacement of the plane
   */
   float getDisplacement() const { return d; }
   /**
      Sets the displacement of the plane
   */
   void setDisplacement( float distance ) { this->d = distance; }
   /**
      
   */
   std::string toString() const;

   float x; ///< X component of plane's normal vector
   float y; ///< Y component of plane's normal vector
   float z; ///< Z component of plane's normal vector
   float d; ///< Distance from origin, along normal direction (assuming normal is normalized)

protected:

};

}

