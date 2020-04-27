#pragma once

#include <string>
#include "Mat4Fwd.h"

#include "Vector.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include <cstdio>
#include "Mat4.h"

namespace Aftr
{

template< typename T >
class QuatT
{
public:
   using value_type = T;

   QuatT();

   /**
      a - the scalar component of the quaternion
      b,c,d - the vector components of the quaternion
   */
   QuatT( T scalarA, T vecCompX, T vecCompY, T vecCompZ );
   QuatT( const T* m4x4 ); ///< convert a rotation matrix to a quaternion
   QuatT( const Mat4T<T>& dcm ); ///< convert a rotation matrix to a quaternion
   QuatT( const QuatT& toCopy );
   virtual ~QuatT();
   QuatT<T> negation()const;
   QuatT<T> conjugation()const;
   QuatT<T> operator+( const QuatT& q ) const;
   QuatT<T> operator-( const QuatT& q ) const;
   QuatT<T> operator*( const QuatT& q ) const;
   QuatT<T>& operator=( const QuatT& q );
   QuatT<T> grassmanProduct( const QuatT& q )const;
   T innerProduct( const QuatT& q )const;
   QuatT<T> outerProduct( const QuatT& q )const;
   T magnitude()const;
   QuatT<T> crossProduct( const QuatT& q )const;
   QuatT<T> evenProduct( const QuatT& q )const;
   void toRepresentationMatrix( T m[16] )const;
   Mat4T<T> toRotationMatrix() const;
   void toRotationMatrix( T m[16] ) const;
   std::string toString() const;
   void normalize();
   QuatT<T> normalizeMe() const;

   /**
      Spherical Linear Interpolation parametricDistance [0..1] between src
      and dst.
      Returned Quaternion is interpolated orientation between src and dst.
      */
   static QuatT slerp( const QuatT& src, const QuatT& dst, T t );

   T a; ///< Scalar component of quaternion
   T b; ///< Vector 'x' component
   T c; ///< Vector 'y' component
   T d; ///< Vector 'z' component
};

using Quat = QuatT<float>;
using QuatD = QuatT<double>;

} //namespace Aftr
#include "Quat.cpptemplate.h"

