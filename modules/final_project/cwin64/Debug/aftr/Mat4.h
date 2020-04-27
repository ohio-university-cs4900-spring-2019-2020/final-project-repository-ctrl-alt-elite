//----------------------------------------------------------------------------
//Description: The Mat4T class is a utility class for reference frame / matrix
//rotations, scalings, and translations. This matrix class is column major and
//assumes all in passed Vectors are also column major. As a result, this class
//performs post multiplication against other Mat4s and Vectors.
//
//Useful operations are also provided to manipulate a Matrices and verticies.
//Additionally, the BIG 3 are implemented.
//
//This class is defined as a templated class that has a user-specified
//storage type. The most expected user specified types are float, double,
//and other floating point types (perhaps long double)?. Either way,
//since float and double are considered the "most common" usages, this
//Mat4T class declares two aliases as defined in MatrixFwd.h. In this file
//Matrix is an alias to Mat4T<float> and MatrixD is an alias to 
//Mat4T<double>.
//
//To PREDECLARE this class in a header file, simply #include "MatrixFwd.h"
//Otherwise, the user will have to retype the alias definitions made
//within MatrixFwd.h.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------
#pragma once
#include "AftrConfig.h"
#include "Mat4Fwd.h"
#include "VectorFwd.h"

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <cstdlib>
#ifdef AFTR_CONFIG_USE_BOOST
   #include <boost/regex.hpp> //Used by Mat4T<T>::Mat4T( const std::string& str )
#endif

namespace Aftr
{

template< typename T >
class Mat4T
{
public:

   using value_type = T;

   static void setToIdentity4x4( T* m );

   ///------------------------------------------------------------------------
   /// Default constructor initializes matrix to identity.
   ///------------------------------------------------------------------------
   Mat4T();
   
   ///------------------------------------------------------------------------
   /// Copy constructor creates a copy of the passed in Matrix.
   /// const Mat4T& m: the Matrix to be copied.
   ///------------------------------------------------------------------------
   Mat4T( const Mat4T& m );

   ///-------------------------------------------------------------------------
   /// Constructor which creates a Matrix from the first 16 elements from the
   /// in passed T* array. T* must contain at least 16 elements or the behavior
   /// is undefined. The in passed T* is only copied so ownership is 
   /// NOT passed to this instance.
   ///-------------------------------------------------------------------------
   explicit Mat4T( const T* Mat4ToBeCopied );

   ///------------------------------------------------------------------------
   /// Constructor which creates a Mat4T from the passed in string.
   /// String str: The str which is parsed to create the Mat4T.
   /// The input format is a string containing at least 3 numbers. A number may
   /// look like: 1.2 0.2 2 .3 1.2e+3 -.3 45.334E-32, etc.
   /// The numbers can be separated by any separator or set of separators that
   /// do not include a format matched by above.
   /// Specifically, given a string, the first 16 matches found by the regular 
   /// expression: "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"
   /// will be used as input.
   /// An input string of " ( 1.23, 56.323e32, -.23 ... , 3 ) " would be
   /// parsed as expected.
   /// If the first 16 values are specified in a row major order (for example,
   /// if 4 rows of numbers separated by newlines), the second param may be
   /// set to false if the input is not column major, to parse properly.
   /// Internally, this matrix is always column major.
   ///------------------------------------------------------------------------
   Mat4T( const std::string& str, bool inputStringIsColumnMajor = true );

   Mat4T( const VectorT<T>& x, const VectorT<T>& y, const VectorT<T>& z );

   Mat4T( std::array<T, 16> const& m );

   ///------------------------------------------------------------------------
   /// Destructor
   ///------------------------------------------------------------------------
   ~Mat4T() {};

   ///------------------------------------------------------------------------
   /// Copies 16 values from the input into this Mat4's internal matrix.
   ///------------------------------------------------------------------------
   void set( const T* mat4x4 );

   ///------------------------------------------------------------------------
   /// Resets the X,Y,Z values to 0.
   ///------------------------------------------------------------------------
   void setMeToIdentity();

   ///------------------------------------------------------------------------
   /// Multiplies the upper 3x3 portion of this matrix by the in passed vector
   /// and returns the resultant Vector. The translation column of this matrix
   /// is NOT added to the result; that is, a Vector (direction only) is
   /// returned. If you would like to transform a vertex, either add the
   /// fourth column of this matrix to the result, or use a Vector4 instance.
   /// Optionally, you may also use the operator * which takes an 
   /// std::pair< Vector<T>, T >, where the second item is the 4th coordinate
   /// (ie, the 'w' in the x,y,z,w in passed values).
   /// Returns: Vector: the column vector transformed by the upper 3x3 of this
   /// submatrix of this matrix; the translation column (4th column) of this
   /// matrix is NOT added to the result.
   ///------------------------------------------------------------------------
   VectorT<T> operator *( const VectorT<T>& v ) const;

   ///------------------------------------------------------------------------
   /// Multiplies a 4 element column major vector by this matrix and returns
   /// a 4 element column major vector. The 4 element vector is broken into 
   /// two parts: A) the first part of the pair, which defines the X,Y,Z
   /// components, and B) the second part of the pair, which defines the X
   /// component.
   /// The resultant 4 element vector is return as an std::pair in the same
   /// format as the input.
   ///------------------------------------------------------------------------
   std::pair< VectorT<T>, T > operator *( const std::pair< const VectorT<T>&, T >& homogeniusCoord ) const;

   ///------------------------------------------------------------------------
   /// Multiplies a 4 element column major vector by this matrix and returns
   /// a 3 
   ///------------------------------------------------------------------------
   ///VectorT<T> multiply4ElementVec( const VectorT<T>& v, T h ) const;
   
   //Scott: contemplate equivalent "translateMe" functions which manipulate the existing object in equivalent ways
   //not sure if this class is implicitly using move semantics, so unsure if this will improve performance in
   //cases where old values are not needed, wasn't immediately obvious as a user that these wouldn't
   //translate the object they were called on
   Mat4T<T> translate( const VectorT<T>& t ) const;
   static Mat4T<T> translateIdentityMat( const VectorT<T>& t );

   ///Scale scales the x, y, and z components of a copy of this by s.x, s.y, and s.z and returns it, to assign the diagonal use setScale()
   Mat4T<T> scale( const VectorT<T>& s ) const;
   static Mat4T<T> scaleIdentityMat( const VectorT<T>& s );

   Mat4T<T> transposeUpperLeft3x3() const;
   Mat4T<T> transpose4x4() const;

   ///------------------------------------------------------------------------
   /// Returns this Matrix rotated about axisNormalied by angleRads degrees.
   /// Internally, an identity matrix is rotated by the in passed params and
   /// then is post multiplied by this matrix.
   /// Return: this matrix rotated by the in passed parameters.
   /// returnMat := rotatedIdentity * (*this); (poaftrultiplication)
   ///------------------------------------------------------------------------
   Mat4T<T> rotate( const VectorT<T>& axisNormalized, T angleRads ) const;

   ///------------------------------------------------------------------------
   /// A static method that always rotates the identity matrix about the in
   /// passed axis by the specified radian amount. This is identical to 
   /// Mat4T<T>::rotate when ::rotate is called on a matrix set to identity.
   /// This method is faster than ::rotate since no internal accumulation 
   /// has to take place; ie, this requires one less matrix multiplication
   /// than rotate.
   /// Returns an identity reference frame rotated about axisNormalized by
   /// angleRad radians.
   ///------------------------------------------------------------------------
   static Mat4T<T> rotateIdentityMat( const VectorT<T>& axisNormalized,
                                      T angleRads );

   ///------------------------------------------------------------------------
   /// Post Multiplies this Matrix by m and returns the result.
   /// Result := thisMatrix * m (column-major using post multiplication).
   /// Returns: Mat4T: the product of this matrix and Matrix m.
   ///------------------------------------------------------------------------
   Mat4T<T> operator *( const Mat4T& m )const;
   Mat4T<T>& operator *=( const Mat4T& m );

   ///------------------------------------------------------------------------
   /// Component wise addition of the two matrices.
   /// Result := thisMatrix + m
   /// Returns: Mat4T: the product of this matrix and Matrix m.
   ///------------------------------------------------------------------------
   Mat4T<T> operator +(const Mat4T& m)const;

   ///------------------------------------------------------------------------
   /// Insertion operator enabling a Mat4T to be read into std::cout << myVec.
   ///------------------------------------------------------------------------
   friend std::ostream& operator <<( std::ostream& out, const Mat4T& m )
   {
      out << m.toString();
      return out;
   }

   ///------------------------------------------------------------------------
   ///Assignment operator assigns the in passed Mat4T's data equal to this 
   ///Mat4T.
   ///m: the Matrix who's data will be used to fill this Mat4T.
   ///------------------------------------------------------------------------
   Mat4T<T>& operator =( const Mat4T& mat );

   ///------------------------------------------------------------------------
   /// Returns true if each component falls within a specified epsilon
   /// to each other.
   /// PARAM const Mat4T& m: the Matrix who's values will be compared to
   /// the values of this Mat4T.
   /// RETURN: True if the X,Y,Z values lie within an epsilon to each other;
   /// false, otherwise.
   ///------------------------------------------------------------------------
   bool operator ==( const Mat4T& m ) const;

   bool operator !=( const Mat4T<T>& m ) const;

   T& operator[]( size_t i );
   T operator[]( size_t i ) const;
   T& at( size_t i );
   T at( size_t i ) const;

   bool isEqual( const Mat4T& m, T tolerance = static_cast<T>( 0.00001 ) ) const;
   static bool is_T_Equal( T x, T y, T epsilon );

   ///------------------------------------------------------------------------
   /// Returns true if each element in this 4x4 matrix is not infinite or not
   /// NaN.
   ///------------------------------------------------------------------------
   bool isValidForEachComponent() const;

   ///------------------------------------------------------------------------
   /// Returns a string representation of the current Mat4T.
   /// Return: string: "(X, Y, Z)" representing the current Mat4T.
   ///------------------------------------------------------------------------
   std::string toString() const;
   std::string toString( size_t length ) const;
   std::string toStringWithVecMagnitudes( size_t length ) const;

   ///------------------------------------------------------------------------
   /// Follows exact same semantics as constructor with same input parameters.
   ///------------------------------------------------------------------------
   static Mat4T<T> fromString( const std::string& str, bool inputStringIsColumnMajor = true );


   //Returns a double precision version of this single precision Mat4T.
   Mat4T< double > toMatD() const;
   Mat4T< float > toMatS() const;

   VectorT<T> getX() const;
   VectorT<T> getY() const;
   VectorT<T> getZ() const;
   VectorT<T> getPosition() const; ///< Returns the position column stored in this matrix. That is, the X,Y,Z values in the 4th column (elements 12,13,14)
   VectorT<T> getVecCol( int i ) const; ///< Returns the ith column vector in this 4x4 matrix (0=X, 1=Y, 2=Z, 3=Pos)

   Mat4T<T> getUpperLeft3x3AsMat4() const;

   void setX( const VectorT<T>& xVec );
   void setY( const VectorT<T>& yVec );
   void setZ( const VectorT<T>& zVec ); 
   void setPosition( const VectorT<T>& transVec ); ///< Sets the X,Y,Z values of the 4th column to in passed value, does not transform through upper 3x3
   void setVecCol( int i, const VectorT<T>& vec ); ///< Sets the ith column vector in this 4x4 matrix (0=X, 1=Y, 2=Z, 3=Pos)
   void setScale( const VectorT<T>& scaleVec ); ///< Sets the Diagonal values (matrix's trace) of the first 3 columns to in passed value. It overwrites the x,y,z scales.
   void multScale(const VectorT<T>& scaleVec);///< Multiplies the diagonal values of the first 3 columns to in passed value.  Effectively the operation of now depricated glScale*()

   ///------------------------------------------------------------------------
   ///Returns a pointer to an array of 16 values, corresponding to this Mat4
   ///internal matrix. Column Major layout as follows:
   ///   0 4  8 12        x0 x1 x2 0
   ///   1 5  9 13  ===>  y0 y1 y2 0
   ///   2 6 10 14  ===>  z0 z1 z2 0
   ///   3 7 11 15         0  0  0 1
   ///
   /// Where Column 0 is the X vector, Column 1 is the Y vector, and
   /// Column 2 is the Z vector in this Mat4.
   ///------------------------------------------------------------------------
   T* getPtr();
   const T* getPtr() const;


   std::array<T,16> m; //The 4x4 matrix

   constexpr T ZERO_THRESHOLD() const { return static_cast<T>( 0.001 ); }

protected:
};

using Mat4 = Mat4T< float >;
using Mat4D = Mat4T< double >;

} //namespace Aftr
#include "Mat4.cpptemplate.h"
