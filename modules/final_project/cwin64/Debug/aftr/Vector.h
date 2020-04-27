//----------------------------------------------------------------------------
//Description: The VectorT class is a utility class which stores a grouping of
//3 Ts. The group of 3 (x,y,z) Ts can represent a vector or a vertex.
//A vector is a force in combination with a direction.
//A vertex is a 3 dimensional point.
//
//Useful operations are also provided to manipulate a vectors and verticies.
//Additionally, the BIG 3 are implemented.
//
//This class is defined as a templated class that has a user-specified
//storage type. The most expected user specified types are float, double,
//and other floating point types (perhaps long double)?. Either way,
//since float and double are considered the "most common" usages, this
//VectorT class declares two aliases as defined in VectorFwd.h. In this file
//Vector is an alias to VectorT<float> and VectorD is an alias to
//VectorT<double>.
//
//To PREDECLARE this class in a header file, simply #include "VectorFwd.h"
//Otherwise, the user will have to retype the alias definitions made
//within VectorFwd.h.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------
#pragma once
#include "VectorFwd.h"

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/regex.hpp> //Used by VectorT<T>::VectorT( const std::string& str )
#endif

#include "AftrGlobals.h"
#include "AftrCoordinateTransforms.h"
#include "AftrEllipsoids.h"
#include "VectorImpl.h"

namespace Aftr
{

template <typename T>
class VectorT
{
  public:
    using value_type = T;

    using iterator = T*;
    using const_iterator = const T*;
    
    iterator begin() noexcept { return &this->x; }
    const_iterator cbegin() noexcept { return &this->x; }
    
    iterator end() noexcept { return &this->z+1; }
    const_iterator cend() noexcept { return &this->z+1; }

    //-------------------------------------------------------------------------
    //Compile time constants to return an x axis, y axis, or z axis.
    //-------------------------------------------------------------------------
    constexpr static VectorT<T> x_axis() { return VectorT{ 1,0,0 }; }
    constexpr static VectorT<T> y_axis() { return VectorT{ 0,1,0 }; }
    constexpr static VectorT<T> z_axis() { return VectorT{ 0,0,1 }; }
    
    //-------------------------------------------------------------------------
    //Compile time constants to return an x axis, y axis, or z axis based on
    //an index 0 (x axis), 1 (y axis), or 2 (z axis).
    //-------------------------------------------------------------------------
    constexpr static VectorT<T> identity_axis( int x0_y1_z2 )
    {
       assert( (x0_y1_z2 >= 0 && x0_y1_z2 <= 2) && "Invalid index for VectorT<T>::identity_axis(...). Must be 0, 1, or 2.\n" );

       if( x0_y1_z2 == 0 ) return x_axis();
       if( x0_y1_z2 == 1 ) return y_axis();
       return z_axis();
    }

    //-------------------------------------------------------------------------
    //Default constructor initializes the x,y,z components to zero.
    //-------------------------------------------------------------------------
    VectorT();

    //-------------------------------------------------------------------------
    //Copy constructor creates a copy of the passed in vector.
    //const VectorT& v: the vector to be copied.
    //-------------------------------------------------------------------------
    VectorT(const VectorT &v);

    //-------------------------------------------------------------------------
    //Constructor which creates a VectorT from three passed in Ts.
    //T x: the x component of the VectorT.
    //T y: the y component of the VectorT.
    //T z: the z component of the VectorT.
    //-------------------------------------------------------------------------
    VectorT(T x, T y, T z);

    //-------------------------------------------------------------------------
    //Constructor which sets the X,Y, and Z elements to the same value of xyz.
    //-------------------------------------------------------------------------
    VectorT( T xyz );

    //-------------------------------------------------------------------------
    //Constructor which creates a VectorT from the passed in string.
    //String str: The str which is parsed to create the VectorT.
    //The input format is a string containing at least 3 numbers. A number may
    //look like: 1.2 0.2 2 .3 1.2e+3 -.3 45.334E-32, etc.
    //The numbers can be separated by any separator or set of separators that
    //do not include a format matched by above.
    //Specifically, given a string, the first 3 matches found by the regular
    //expression: "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"
    //will be used as input.
    //An input string of " ( 1.23, 56.323e32, -.23 ) " would be parsed as
    //expected.
    //-------------------------------------------------------------------------
    VectorT(const std::string &str);

    //-------------------------------------------------------------------------
    //Constructor which creates a vector from the in passed VectorT*. The in
    //passed VectorT* is only copied so ownership is NOT passed to this
    //instance.
    //-------------------------------------------------------------------------
    explicit VectorT(const VectorT *vectorToBeCopied);

    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    VectorT(T v[]);

    //-------------------------------------------------------------------------
    //Constructs a 3D VectorT using the first 3 values in
    //std::vector< T > v. If fewer than 3 values in v, zeros are inserted.
    //-------------------------------------------------------------------------
    VectorT(std::vector<float> &v);

    //-------------------------------------------------------------------------
    //Constructs a 3D VectorT using the first 3 values in
    //std::vector< double > v. If fewer than 3 values in v, zeros are inserted.
    //-------------------------------------------------------------------------
    VectorT(std::vector<double> &v);

    //-------------------------------------------------------------------------
    //Destructor
    //-------------------------------------------------------------------------
    ~VectorT() = default;

    //-------------------------------------------------------------------------
    //Resets the X,Y,Z values to 0.
    //-------------------------------------------------------------------------
    void clear();

    //-------------------------------------------------------------------------
    //Adds vector v to this vector in a component-wise manner.
    //Returns: VectorT: the sum of vector v and this vector.
    //-------------------------------------------------------------------------
    //VectorT<T> operator+(const VectorT &v) const;
    friend VectorT<T> operator+( const VectorT& a, const VectorT& b )
    {
       return VectorT<T>( a.x + b.x, a.y + b.y, a.z + b.z );
    }

    //-------------------------------------------------------------------------
    //Adds T d to each component of this vector.
    //Returns: VectorT: the sum of T d to each component of this vector.
    //-------------------------------------------------------------------------
    VectorT<T> operator+(const T &d) const;

    //-------------------------------------------------------------------------
    //Subtracts vector v from this vector in a component-wise manner.
    //Returns: VectorT: the difference of this vector and vector v.
    //-------------------------------------------------------------------------
    VectorT<T> operator-(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Subtracts T d from each component of this vector.
    //Returns: VectorT: the difference of this vector v and T d.
    //-------------------------------------------------------------------------
    VectorT<T> operator-(const T &d) const;

    //-------------------------------------------------------------------------
    //Multiplies vector v to this vector in a component-wise manner.
    //Returns: VectorT: the product of vector v and this vector.
    //-------------------------------------------------------------------------
    VectorT<T> operator*(const VectorT &v) const;
    VectorT<T> operator*=(const VectorT &v);

    //-------------------------------------------------------------------------
    //Multiplies T d to each component of this vector.
    //Returns: VectorT: the product of T d and each component of this
    //vector.
    //-------------------------------------------------------------------------
    VectorT<T> operator*(const T &d) const;
    VectorT<T> operator*=(const T &d);

    //-------------------------------------------------------------------------
    //Divides this vector by vector v in a component-wise manner.
    //Returns: VectorT: the vector of quotients of this vector divided by
    //vector v in a component-wise manner.
    //-------------------------------------------------------------------------
    VectorT<T> operator/(const VectorT &v) const;
    VectorT<T> operator/=(const VectorT &v);

    //-------------------------------------------------------------------------
    //Divides each component of this vector by T d.
    //Returns: VectorT: a vector of quotients of each component of this vector
    //divided by T d.
    //-------------------------------------------------------------------------
    VectorT<T> operator/(const T &d) const;
    VectorT<T> operator/=(const T &d);

    //-------------------------------------------------------------------------
    // Adds another vector to this one and replaces this vector's components
    // with the result
    //-------------------------------------------------------------------------
    VectorT<T> operator+=(const VectorT &v);
    VectorT<T> operator-=(const VectorT &v);

    //-------------------------------------------------------------------------
    // Extraction operator enabling a VectorT to be read in std::cin >> myVec.
    // Expected input is: ( 123.456, 46.43343432432, 122333.1 )
    //-------------------------------------------------------------------------
    friend std::istream &operator>>(std::istream &in, VectorT &v)
    {
       char unused = 0;
       in >> unused; //get the "("
       in >> v.x;
       in >> unused; //get the ","
       in >> v.y;
       in >> unused; //get the ","
       in >> v.z;
       in >> unused; //get the ")"

       return in;
    }

    //-------------------------------------------------------------------------
    // Insertion operator enabling a VectorT to be read in std::cout << myVec.
    //-------------------------------------------------------------------------
    friend std::ostream &operator<<(std::ostream &out, const VectorT &v)
    {
       out << v.toString();
       return out;
    }

    //-------------------------------------------------------------------------
    //Returns a VectorT containing the difference of the two operand Vectors.
    //VectorT* v: the vector to be subtracted from this vector.
    //Return: VectorT*: the difference of the two vectors.
    //-------------------------------------------------------------------------
    VectorT<T>* minus( VectorT *v ) const;

    //-------------------------------------------------------------------------
    //Assignment operator assigns the in passed VectorT's data equal to this
    //VectorT.
    //VectorT* v: the vector who's data will be used to fill this VectorT.
    //-------------------------------------------------------------------------
    void operator=(VectorT *v);

    //-------------------------------------------------------------------------
    //Assignment operator assigns the in passed VectorT's data equal to this
    //VectorT.
    //v: the vector who's data will be used to fill this VectorT.
    //-------------------------------------------------------------------------
    VectorT<T> &operator=(const VectorT &v);

    //-------------------------------------------------------------------------
    //Returns true if the X, Y, and Z values are fall within a specified epsilon
    //to each other.
    //PARAM const VectorT& v: the vector who's X,Y,Z values will be compared to
    //the X,Y,Z values of the left hand side VectorT.
    //RETURN: True if the X,Y,Z values lie within an epsilon to each other;
    //false, otherwise.
    //-------------------------------------------------------------------------
    bool operator==(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns true if the X, Y, and Z values are identical to each other.
    //PARAM const VectorT& v: the vector who's X,Y,Z values will be compared to
    // the X,Y,Z values of the left hand side VectorT.
    //RETURN: True if the X,Y,Z values do not lie within an epsilon to each
    //other; false, otherwise.
    //-------------------------------------------------------------------------
    bool operator!=(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns true if this vector is "less than" vector v.
    //"Less than" compares the magnitudes of the two vectors
    //RETURN: True if the this is less than v; false, otherwise.
    //-------------------------------------------------------------------------
    bool operator<(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns true if this vector is "greater than" vector v.
    //"Greater than" compares the magnitudes of the two vectors
    //RETURN: True if the this is greater than v; false, otherwise.
    //-------------------------------------------------------------------------
    bool operator>(const VectorT &v) const;

    T &operator[](size_t i);
    T operator[](size_t i) const;
    T &at(size_t i);
    T at(size_t i) const;

    bool isEqual(const VectorT &v, T tolerance = 0.00001f) const;

    //-------------------------------------------------------------------------
    //Returns true if the x,y, and z components are all Ting point values
    //that are normal, i.e., not nan, not inf, but a finite, valid, numerical
    //value. This requires usage of the boost library. If boost is not used
    //a slightly non-portable IEEE specific technique is used that may always
    //return true given the specific compiler optimizations (IEEE says that
    //x != x is true whenever x is not a valid T. When boost is not used,
    //a warning cout is also given.
    //-------------------------------------------------------------------------
    bool isValidForEachComponent() const;

    //-------------------------------------------------------------------------
    //Returns a VectorT containing the cross product of the two operand Vectors.
    //The cross product represents a VectorT that is perpendicular to the to
    //operand Vectors.
    //Note: returned cross product is not necessarily of unit length
    //VectorT* v: the vector to be crossed with this vector.
    //Return: VectorT*: the cross product of the two vectors.
    //-------------------------------------------------------------------------
    VectorT<T>* crossProduct( VectorT *v ) const;

    //-------------------------------------------------------------------------
    //Returns a VectorT containing the cross product of the two operand Vectors.
    //The cross product represents a VectorT that is perpendicular to the to
    //operand Vectors.
    //VectorT& v: the vector to be crossed with this vector.
    //Return: VectorT: the cross product of the two vectors.
    //-------------------------------------------------------------------------
    VectorT<T> crossProduct(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns a T containing the dot product of the two operand Vectors.
    //The dot product represents the angle between to vectors in radians.
    //VectorT* v: the vector to be dotted with this vector.
    //Return: T: the dot product of the two vectors.
    //-------------------------------------------------------------------------
    T dotProduct(VectorT *v) const;

    //-------------------------------------------------------------------------
    //Returns a T containing the dot product of the two operand Vectors.
    //The dot product represents the angle between to vectors in radians.
    //VectorT& v: the vector to be dotted with this vector.
    //Return: T: the dot product of the two vectors.
    //-------------------------------------------------------------------------
    T dotProduct(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns the vector projection of this vector projected onto v.
    //The vector projection of A on B is the orthogonal projection of
    //A onto the straight line defined by B.
    //The vector projection of A on B can be also regarded as the
    //corresponding scalar projection A.scalarProjectionOnto(B) multiplied by
    //B.normalized().
    //For this method, A corresponds the 'this' vector and B corresponds to
    //the in passed v vector.
    //-------------------------------------------------------------------------
    VectorT<T> vectorProjectOnto(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns the scalar projection of this vector onto v.
    //The scalar projection is a scalar, and is the length of the orthogonal
    //projection of the vector A onto the vector B, with a minus sign if the
    //direction is opposite.
    //Multiplying the scalar projection by B.normalized() converts it into
    //the vector projection, a vector (same as calling
    //VectorT::vectorProjectOnto(...).
    //For this method, A corresponds the 'this' vector and B corresponds to
    //the in passed v vector.
    //-------------------------------------------------------------------------
    T scalarProjectionOnto(const VectorT &v) const;

    //-------------------------------------------------------------------------
    //Returns the result of projecting this vector onto the plane defined
    //by the in passed normal.
    //Orthogonal projection U = VectorT V projected onto plane
    //defined by normalized normal N:
    //U = V - (V dot N)N
    //-------------------------------------------------------------------------
    VectorT<T> vectorProjectOnToPlane(const VectorT &planeNormal) const;

    //-------------------------------------------------------------------------
    //Scales the VectorT's magnitude such that it is exactly 1.  Direction is
    //preserved; that is, the ratio of the X, Y, and Z components are
    //unchanged. If you want to leave this vector unchanged, but have the
    //normalization returned, use VectorT::normalizeMe().
    //-------------------------------------------------------------------------
    void normalize();

    //-------------------------------------------------------------------------
    //Returns a VectorT that scales this VectorT's magnitude such that it is
    //exactly 1.  Direction is preserved; that is, the ratio of the X, Y,
    //and Z components are unchanged. If you want to simply normalize this
    //vector without a VectorT being returned, use VectorT::normalize().
    //-------------------------------------------------------------------------
    VectorT<T> normalizeMe() const;

    //-------------------------------------------------------------------------
    //Returns the current magnitude of this VectorT.
    //Return: T: the current magnitude of this VectorT.
    //-------------------------------------------------------------------------
    T magnitude() const;

    //-------------------------------------------------------------------------
    //Returns the current magnitude squared of this VectorT. This is FASTER
    //than magnitude() because the sqrt is not applied to the sum of the
    //components squared.
    //Return: T: the current squared magnitude of this VectorT.
    //-------------------------------------------------------------------------
    T magnitudeSquared() const;

    //-------------------------------------------------------------------------
    //Returns the magnitude of the vector going from the end of this vector
    //to the end of vector v
    //Return: T: the distance between the end of this vector and the end
    //   of v.
    //-------------------------------------------------------------------------
    T distanceFrom(const VectorT &v) const;

    //-------------------------------------------------------------------------
    // Returns this vector rotated by phi and theta (spherical coordinates).
    // Rotation happens by phi (y-axis), then theta (z-axis). This is
    // consistent with all other rotations implemented in this engine.
    // Return: this vector rotated by phi and theta
    //-------------------------------------------------------------------------
    VectorT<T> rotate(T phi, T theta) const;

    //-------------------------------------------------------------------------
    // Rotates this vector about an arbitrary vector in three-space
    // rotVector: the vector to rotate about
    // angle: angle in radians to rotate by.  positive angles rotate counter-
    //    clockwise from the point of view of the origin looking in the
    //    direction of rotVector
    // Return: this vector rotated about the given line by the given angle
    //-------------------------------------------------------------------------
    VectorT<T> rotate(const VectorT &rotVector, T angleRad) const;

    //-------------------------------------------------------------------------
    // Transforms the current vector through the in passed matrix and returns
    // the result. The in passed matrix is assumed to be a column major matrix.
    // Therefore, this vector becomes a column vector placed on the right side
    // of column major matrix m. This vector is then post multiplied by m and
    // the result is returned. The fourth column and row of 'm' are ignored
    // and assumed to be identity.
    //-------------------------------------------------------------------------
    VectorT<T> transformBy44ColMajorMat(const T m[16]) const;

    //-------------------------------------------------------------------------
    // Transforms the current vector through the in passed matrix and returns
    // the result. The in passed matrix is assumed to be a column major matrix.
    // Therefore, this vector becomes a column vector placed on the right side
    // of column major matrix m. This vector is then post multiplied by m and
    // the result is returned.
    //-------------------------------------------------------------------------
    VectorT<T> transformBy33ColMajorMat(const T m[9]) const;

    //-------------------------------------------------------------------------
    //Returns a string representation of the current VectorT.
    //Return: string: "(X, Y, Z)" representing the current VectorT.
    //To ensure full precision is output, one may use:
    //std::numeric_limits<T>::max_digits10
    //-------------------------------------------------------------------------
    std::string toString() const;
    std::string toString(int length) const;
    
    //-------------------------------------------------------------------------
    //Converts the full binary X Y Z components of type T to a base 64 encoded
    //string. Using this in combination with fromStringBase64 will guarantee
    //that no precision or round off errors will occur. Endianness is not
    //considered in this method, so it may be an issue if this is serialized
    //and deserialized across different processors.
    //For VectorT<double>: returned string contains 32 ascii base64 characters.
    //For VectorT<float>: returned string contains 16 ascii base64 characters.
    //-------------------------------------------------------------------------
    std::string toStringBase64() const;

    //-------------------------------------------------------------------------
    //Converts a base 64 string generated by toStringBase64 to a VectorT<T>
    //Using this in combination with toStringBase64 will guarantee
    //that no precision or round off errors will occur. Endianness is not
    //considered in this method, so it may be an issue if this is serialized
    //and deserialized across different processors.
    //-------------------------------------------------------------------------
    static VectorT<T> fromStringBase64( const std::string& s );

    VectorT<T>& fromString(const std::string &str);

    //-------------------------------------------------------------------------
    //Returns the radian measure of the horizontal offset between this VectorT
    //and the global +X Axis. Valid return values are [-PI,PI].
    //-------------------------------------------------------------------------
    T getTheta() const;

    //-------------------------------------------------------------------------
    //Returns the radian measure of the vertical offset between this VectorT
    //and the global +Z Axis. Valid return values are [0,PI].
    //-------------------------------------------------------------------------
    T getPhi() const;

    //---------------
    //assumes this->x is a latitude and this->y is a longitude and this->z is the altitude
    //converts the lat/long pair to ECEF coordinates using WGS-84
    //---------------
    VectorT<T> toECEFfromWGS84() const;
    VectorT<T> toECEFfromGRS80() const;
    //---------------
    //assumes the vector is currently in ECEF and converts it to WGS-84
    VectorT<T> toWGS84fromECEF() const;

    //---------------
    //assumes this->x is a latitude and this->y is a longitude and this->z is the altitude (ignored)
    //converts the lat/long pair to ECEF coordinates using GRS80 (only works for northern hemisphere, will investigate later)
    //---------------
    VectorT<T> toCartesianFromLambertConformalConicUsingGRS80Ellipsoid(T referenceLat, T referenceLon, T parallel1, T parallel2); //should probably update these kind of functions to take an ellipsoid object
    VectorT<T> toGRS80FromLambertConformalConic(T referenceLat, T referenceLon, T parallel1, T parallel2);			  //should probably update these kind of functions to take an ellipsoid object
    VectorT<T> toGRS80FromTransverseMercator(T originalLat, T originaLon, T falseNorthing, T falseEasting);			  //
    VectorT<T> toTransverseMercatorFromGRS80(T originLat, T originLon, T k0);

    //Returns a double precision version of this single precision VectorT.
    VectorT<double> toVecD() const;
    VectorT<float> toVecS() const;

    //---------------
    //Enables a VectorT<T> to be cast between a VectorT<float> and VectorT<double>
    //and vice-versa. With the below two methods, the following code compiles and
    //works as expected:
    //VectorT<double> vecD = static_cast<VectorT<double>>( VectorT<float>(1.0f,2.0f,3.0f) )
    //VectorT<float> vecD = static_cast<VectorT<float>>( VectorT<double>( 1.0,2.0,3.0) )
    //---------------
    operator VectorT<double>() const { return VectorT<double>{x, y, z}; }
    operator VectorT<float>() const { return VectorT<float>{x, y, z}; }

    T x; //The X component
    T y; //The Y component
    T z; //The Z component

    constexpr T ZERO_THRESHOLD() const { return static_cast<T>( 0.001 ); }

  protected:
};

using Vector = VectorT<float>;
using VectorD = VectorT<double>;

} //namespace Aftr
#include "Vector.cpptemplate.h"
