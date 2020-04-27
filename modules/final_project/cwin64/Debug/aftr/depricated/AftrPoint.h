#pragma once

#include <cmath>

namespace Aftr
{

class SphericalVector;

class AftrPoint
{
public:
   AftrPoint( float xv = 0, float yv = 0, float zv = 0 );
   AftrPoint( float* l );
   //AftrPoint(GLfloat p[3]);
   AftrPoint operator+( const AftrPoint& p2 )const;
   AftrPoint operator+=( const AftrPoint& p2 );
   AftrPoint operator+( const SphericalVector& v1 )const;
   AftrPoint operator+=( const SphericalVector& v1 );
   AftrPoint getNormal( const AftrPoint& p1, const AftrPoint& p2 );
   float x(){ return X; }
   void x( float i ){ X = i; }
   float y(){ return Y; }
   void y( float i ){ Y = i; }
   float z(){ return Z; }
   void z( float i ){ Z = i; }
   float* getAll();
   float distanceTo( const AftrPoint& given )const { return sqrt( pow( X - given.X, 2 ) + pow( Y - given.Y, 2 ) + pow( Z - given.Z, 2 ) ); }
   SphericalVector toVector()const;///< returns a vector from the origin to the point
private:
   float X;///< value of x-coordinate
   float Y;///< value of y-coordinate
   float Z;///< value of z-coordinate
};

}

