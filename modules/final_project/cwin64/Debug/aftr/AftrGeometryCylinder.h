#pragma once

#include "Vector.h"
#include <string>

namespace Aftr
{
	
class AftrGeometryCylinder
{
public:
   /**
      Default constructor
   */
   AftrGeometryCylinder();
   /**
      Constructor taking each element
   */
   AftrGeometryCylinder( const Vector& majorAxisDir, float radius );

   /**
      Center of cylinder is at height / 2.0f
   */
   AftrGeometryCylinder( const Vector& majorAxisDir, float radius, float height );
   /**
      Default destructor
   */
   virtual ~AftrGeometryCylinder() {}

   /**
      Returns the normalized major axis
   */
   Vector getMajorAxisNormalized() const { return this->majorAxis; }

   /**
      Sets major axis of cylinder
   */
   void setMajorAxis( const Aftr::Vector& majorAxis );

   float getRadius() const { return this->r; };
   void setRadius( float radius ) { this->r = radius; }

   /**
      Returns true if this cylinder is a finite height. Returns false if this cylinder is infinitely tall.
      If this returns true, the specified height is used; otherwise, the height is ignored. This is used
      inside the AftrUtilities::intersectLineCylinder(...) method.
   */
   bool isCapped() const { return this->IsCapped; }
   void isCapped( bool isFiniteHeight ) { this->IsCapped = isFiniteHeight; }

   float getHeight() const { return this->h; }
   void setHeight( float heightOfCylinder ) { this->h = heightOfCylinder; }


   /**
      Returns a string of this cylinder's state      
   */
   virtual std::string toString() const;

protected:
   Vector majorAxis;
   float r; ///< radius of cylinder
   bool IsCapped; ///< if true, the cylinder is of the specified height and is not infinitely tall
   float h; ///< if isCapped == true, this defines the height of the cylinder; if isCapped == false, this is not used

};

}

