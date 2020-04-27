#pragma once

#include "Vector.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace Aftr
{

class AftrPoint;

class SphericalVector
{
 public:
  SphericalVector(float m = 1, float xi = 0, float zi = 0);
  SphericalVector(AftrPoint start, AftrPoint end, float m = 1);//generates a SphericalVector that is the transition vector from start to end (normal vector by default, can give a magnitude)
  SphericalVector(const Vector& v);
  SphericalVector operator+(const SphericalVector& v2)const;
  SphericalVector operator+=(const SphericalVector& v2);
  SphericalVector operator-(const SphericalVector& v2)const;
  SphericalVector operator*(const float x)const;
  SphericalVector operator/(const float x)const;
  float DotProduct(const SphericalVector& v2);
  SphericalVector CrossProduct(const SphericalVector& v2);
  float magnitude(){return mag;}
  float getPhi()const{return phi;}
  float getTheta()const{return theta;}
  void setTheta(float t){theta = t;}  
  void setPhi(float p){phi = p;}
  void magnitude(float m){mag = m;}
  SphericalVector& normalize();
  float getDX()const{return mag*sin(phi)*sin(theta);}//gets vector magnitude exclusively in the x direction
  float getDY()const{return mag*cos(theta);}//gets vector magnitude exclusively in the y direction
  float getDZ()const{return mag*cos(phi)*sin(theta);}//gets vector magnitude exclusively in the z direction
  Vector toPoint()const;//returns the point that would be at the origin plus the vector
  Vector toCartesianVector()const;
 private:  
  float mag;//length 1 for unit vectors
  float theta;//in radians
  float phi;//in radians
};

}
