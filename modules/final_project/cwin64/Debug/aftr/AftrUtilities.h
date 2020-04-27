#pragma once

#include "AftrConfig.h"
#include <vector>
#include <string>
#include <chrono>
#include <optional>
#include "AftrGeometryTriangleIndexed.h"
#include "AftrGlobals.h"
#include "AftrOpenGLIncludes.h"
#include "Complex.h"
#include "Vector.h"
#include "Mat4Fwd.h"
#include "MatrixFwd.h"

struct SDL_KeyboardEvent;
struct SDL_Surface;

//boost::posix_time::ptime
namespace boost
{
   namespace posix_time
   {
      class ptime;
   }
   namespace gregorian
   {
      class date;
   }
}

namespace Aftr
{
   class AftrPolynomialSingleVariable;
   class AftrGeometryPlane;
   class AftrGeometryAABB;
   class AftrGeometryOBB;
   class AftrGeometryFrustum;
   class AftrFrameCapture;
   class ModelMeshRenderDataGenerator;
   class AftrGeometryCylinder;
   struct tColorRGBA;

   enum class AftrGeometricTerm : unsigned char { geoSUCCESS = 0, geoPARALLEL, geoPERPENDICULAR, geoCOPLANAR, geoUNDEFINED, geoERROR, geoINSIDE, geoOUTSIDE, geoMAX_GEOMETRIC_TERMS };
   std::ostream& operator<<( std::ostream& out, const AftrGeometricTerm& geo );

class AftrUtilities
{
public:

   /// Returns the number of GPS Leap seconds that have occurred thus far as of 22 Aug 2017.
   /// For now, this constant must be maintained manually. The following websites keep count of the leap events:
   //http://tycho.usno.navy.mil/leapsec.html //https://www.endruntechnologies.com/leap.htm
   /// Updated 22 Aug 2017: A total of 18 leap seconds have occurred since Jan 6 1980
   static constexpr unsigned int getNUM_GPS_LEAP_SECONDS() { return 18; }

   static bool readASCIITxtFile( const std::string& pathToFile, std::string& outContents );
   static bool readASCII3DVecListFromFile( const std::string& pathToFile, std::vector< Vector >& vectors );

   /**
      Converts in passed data to standard 72 column base 64 lettering.
   */
   static std::string encodeBinaryToBase64( const std::vector<unsigned char>& data );
   /// Any extra padding at the end "==" or "=" will be ignored when converting to binary.
   static std::vector< unsigned char > encodeBase64ToBinary( const std::string& base64Str );

   static ModelMeshRenderDataGenerator* convertVerticesToGridedTriangles( float* vertices, int x, int y );

   ///finds a convex hull starting with the vertex with great x value, and sorted clockwise from there
   ///implemented as a Graham's Scan O(n lg n)
   static std::vector< Vector > convexHull( const std::vector< Vector >& points, std::vector< int >& indices );
   static std::vector< VectorD > convexHull( const std::vector< VectorD >& points, std::vector< int >& indices );
   ///takes a convex hull of points and removes non extreme points from the hull (not implemented)
   static std::vector< Vector > pruneColinearPointsFromConvexHull( const std::vector< Vector >& points );

   /**
      Given a 3D planar triangle via triPtA..C, and a point contactPt. Compute the linear interpolation of
      contactPt along each of the triangle's three vectors AtoB, BtoC, and CtoA.

      Returns a Vector such that:
      Vec.x = parametric distance of contactPt along triPtA to triPtB.
      Vec.y = parametric distance of contactPt along triPtB to triPtC.
      Vec.z = parametric distance of contactPt along triPtC to triPtA.

      Therefore, if contactPt lies exactly on the edge or inside of the triangle, each component
      in the returned Vector will be in the range [0,1].

      More specifically, let A=triPtA, B=triPtB, C=triPtC, W=contactPt
      ret.x = AtoW.scalarProjectionOnto( AtoB ) / AtoB.magnitude();
      ret.y = BtoW.scalarProjectionOnto( BtoC ) / BtoC.magnitude();
      ret.z = CtoW.scalarProjectionOnto( CtoA ) / CtoA.magnitude();
   */
   static Vector trilinearlyInterpolatePointInTriangle( const Vector& triPtA, const Vector& triPtB, const Vector& triPtC,
                                                        const Vector& contactPt );
   /**
      Returns the barycentric parameters for point p with respect to triangle (a,b,c).
      Returned vector .xyz correspond to barycentric coordinates (u,v,w), respectively.
   */
   static Vector computeBarycentricCoefficientsForPointP( const Vector& a, const Vector& b, 
                                                          const Vector& c, const Vector& p );

   /// Computes the area of a 2D triangle, this method only considers the .xy components
   /// of points a, b, and c. Used within the computeBarycentricCoefficientsForPtP(...).
   /// (side effect is likely that the sign of the area defines the winding order)
   static float computeTriangleArea2D( float x1, float y1, float x2, float y2, float x3, float y3 );
   /// Similar to the above, for for any convex n-gon (lengths of xCoords and yCoords should match, returns 0 otherwise)
   //uses n x 2 determinate method
   static double computeConvexPolygonArea2D( const std::vector< double >& xCoords, const std::vector< double >& yCoords );


   //takes a vertex list and an index list and prints their values
   //static std::string toStringIndexAndVertexList(  );

   //takes 4 corner vertices and see if 5th vertex is inside them.  Parameters are 2D, may or may not be useful to have a 3D version that also makes sure it's in the plane?
   //or in the infinite prism extruded from the plane?
   //if it lies exactly on the edge of the plane, it is inside
   static bool isInsideQuad( GLfloat* first, GLfloat* second, GLfloat* third, GLfloat* fourth, GLfloat* vertex );

   /**
      Intersects the in passed ray against the surface defined within the in passed cylinder. True
      is returned if the ray passes through the surface; false, otherwise. This method checks if the cylinder
      is capped or not. If capped, the capped line intersection method is called. If not capped, the cylinder
      is assumed to be infinitely.

      If the ray is fully contained inside the cylinder, NO intersection is reported. In this case,
      the user may call pointInclusionCylinder(...) to see if either end point of the ray resides
      within the cylinder's volume.
   */
   static bool intersectLineCylinder( const Vector& rayHead, const Vector& rayTail, const AftrGeometryCylinder& c, float& outParametricDistToFirstCollision ); 
   static bool intersectLineCylinderCapped( const Vector& rayHead, const Vector& rayTail, const AftrGeometryCylinder& c, float& outParametricDistToFirstCollision );

   static bool pointInclusionCylinder( const AftrGeometryCylinder& cylinder, const Vector& pt );
   static bool pointInclusionCylinderCapped( const AftrGeometryCylinder& cylinder, const Vector& pt );

   /**
      Perform Gauss-Jordan elimination with row-pivoting to obtain the solution to
      the system of linear equations. Given A and B, solve for X. All matrices are
      the same dimensionality.
      
      A X = B

      Arguments:
      lhs      - left-hand side of the equation, matrix A
      rhs      - right-hand side of the equation, matrix B
      nrows    - number of rows in the arrays lhs and rhs
      ncolsrhs - number of columns in the array rhs

      The function uses Gauss-Jordan elimination with pivoting.  The solution X to
      the linear system winds up stored in the array rhs; create a copy to pass to
      the function if you wish to retain the original RHS array.

      Passing the identity matrix as the rhs argument results in the inverse of
      matrix A, if it exists.

      Code originally from http://www.dreamincode.net/code/snippet1312.htm
   */
   template< typename T >
   static bool gaussianJordanElimination( T** lhs, T** rhs, int nrows, int ncolsrhs );

   /// Helper function called by gaussianJordanElimination
   template< typename T >
   static void gaussianJordanEliminationSwapRows( T** arr, int row0, int row1 );

   //lla1 and lla2 are positions, function returns distance between the two along a WGS84 Geoid
   static double inverseVincentyFormula( const VectorD& lla1, const VectorD& lla, double& azimuth1, double& azimuth2 );
   //returns a point on a WGS84 spheroid 
   static VectorD directVincentyFormula( const VectorD& lla, double heading, double distance );

   static double calculateAzimuthalHeadingBetweenTwoLLAs( const VectorD& lla1, const VectorD& lla2 );

   ///helper linear interpolation 't' of the way between 'a' and 'b'
   static float lerp( float a, float b, float t );

   ///helper linear interpolation 't' of the way between 'a' and 'b'
   static double lerp( double a, double b, double t );

   template< typename T, typename P = double >
   static T lerp( T a, T b, P t )
   {
      T x = (a + (b - a) * t);
      return x;
   }

   /// Converts a Hue, Saturation, Value Color to Red, Green, Blue.
   /// Assumes all color values are floating point values in the range [0,1]
   /// Input: hsv.x -> hue, hsv.y -> saturation, hsv.z = value
   /// Return .x -> red, .y -> green, .z -> blue
   ///
   /// Hue is a value [0,1] that maps to [0,360) degrees.
   /// Saturation is how intense the color is. 1 is "full" color, 0 is all while, 0.5 is "washed out / faded"
   /// Value is how bright the color is. 1 is full brightness, 0 is black, 0.5 is half way.
   /// 0.0000 (0   deg) --> Red
   /// 0.1667 (60  deg) --> Yellow
   /// 0.3333 (120 deg) --> Green
   /// 0.5000 (180 deg) --> Cyan
   /// 0.6667 (240 deg) --> Blue
   /// 0.8333 (300 deg) --> Magenta
   /// 1.0    (360 deg) --> Red
   /// If I wanted to create a Red Color and linearly interpolate it to across HSV, I would do:
   /// Vector hsv_startColor{0,1,1}; //this is red
   /// Vector hsv_endColor{0.8333,1,1}; //this is magenta
   /// Then linearly interpolate from [0, 0.8333] and at each step convert the HSV color to RGB and use that as the color
   static Vector convertHSVtoRGB( const Vector& hsv );
   
   //assumes 0..255
   static Vector convertRGBtoXYZ( const Vector& rgb255 );
   //using D65 white reference, D50 white reference is Vector(0.9642f,1.0f, 0.8249f)
   static Vector convertXYZtoCIELAB( const Vector& xyz, const Vector& referenceWhite = Vector( 0.95047f, 1.0f, 1.08883f ) );
   static Vector convertXYZtoRGB( const Vector& xyz );
   static Vector convertCIELABtoCIELCH( const Vector& lab );
   static Vector convertCIELABtoXYZ( const Vector& lab, const Vector& referenceWhite = Vector( 0.95047f, 1.0f, 1.08883f ) );

   ///returns the luminance (gray-scale) value for a given RGB value
   static double convertRGBtoLuminance( const Vector& rgb );
   static double convertRGBtoLuminance( unsigned char red, unsigned char green, unsigned char blue );

   //Fast Fourier Transform
   //if size(f) != 2^n, then it is padded with 2^n - size(f) 0s, for the smallest 2^n > size(f)
   //this is a O(N lg N) divide and conquer implementation
   static void fft(  std::vector< Aftr::Complex >& f );
   static void fft(  std::vector< std::vector< Aftr::Complex > >& f);
   static void ifft(  std::vector< Aftr::Complex >& f );
   static void ifft(  std::vector< std::vector< Aftr::Complex > >& f);

   /// converts an integer to a string, i.e. 1 -> "1", 346 -> "346" ...
   static std::string toString( int x ) { return std::to_string( x ); }
   static std::string toString( unsigned int x ) { return std::to_string( x ); }
   static std::string toString( float x ) { return std::to_string( x ); }
   static std::string toString( double x ) { return std::to_string( x ); }

   /// converts a string to an integer, i.e. "1" -> 1, "-123" -> -123, ...
   static int toInt( const std::string& value ); ///< Returns "0" if string is does not contain numeric value
   static bool toBool( const std::string& x ); ///< Returns false if x is "0" or "false" (case insenstive); true, otherwise
   static float toFloat( const std::string& value ); ///< Returns "0" if string is does not contain numeric value
   static double toDouble( const std::string& value ); ///< Returns "0" if string is does not contain numeric value
   static unsigned int toUnsignedInt( const std::string& value ); ///< Returns "0" if string is does not contain numeric value

   /// \return a string for the ordinal form of a number, i.e. 1st, 2nd, 3rd, 4th...
   std::string toOrdinalForm( int x );

   /**
      Given a raw array of xyz floats with numVert xyz triplets, return a string printing each vector.
      Optionally, if columnWidth is non zero, print each vector with it's corresponding row, col index.
      Otherwise just the index is printed.

      With zero columnWidth:
      v[i]=x.xxx,y.yyy,z.zzz

      With non-zero columnWidth:
      v[row,col]=x.xxx,y.yyy,z.zzz
   */
   static std::string printOpenGLVertexList( GLfloat* vertices, size_t numVerts, size_t columnWidth = 0 );

   /**
      Given a raw array of UV floats with numVert UV pairs, return a string printing each UV coordinate.
      Optionally, if columnWidth is non zero, print each UV's coord with it's corresponding row, col index.
      Otherwise just the index is printed.

      With zero columnWidth:
      t[i]=u.uuu,v.vvv

      With non-zero columnWidth:
      v[row,col]=u.uuu,v.vvv
   */
   static std::string printOpenGLTex2DList( GLfloat* texCoords, size_t numVerts, size_t columnWidth = 0 );

   /**
      Given a raw array of GLuint indices, return a string printing each index.
      Optionally, if columnWidth is non zero, print each vector with it's corresponding row, col index.
      Otherwise just the index is printed.

      With zero columnWidth:
      idx[i]=a

      With non-zero columnWidth:
      v[row,col]=a
   */
   static std::string printOpenGLIndexList( GLuint* indices, size_t numIndices, size_t columnWidth = 0 );

#ifdef AFTR_CONFIG_USE_BOOST
   /// Splits contents based on the regular express regEx. This works just like Java's String::split method.
   static std::vector< std::string > regExSplit( const std::string& contents, const std::string& regEx );

   /// Finds and returns each occurrence within contents that is matched by the regular expression contained inside regEx.
   static std::vector< std::string > regExMatchAllOccurrences( const std::string& contents, const std::string& regEx );

   /// Converts a boost::posix_time into a human readable string
   /// according to the boost spec at /// according to the boost spec at
   /// http://www.boost.org/doc/libs/1_48_0/doc/html/date_time/date_time_io.html#date%5Ftime.format%5Fflags
   /// Default format string is "%Y %b %d %H:%M:%S.%f"
   static std::string aftrBoostPTimeToString( const boost::posix_time::ptime* t );

   static void aftrConvertPTimeToGPSTime( const boost::posix_time::ptime* t, unsigned int& gpsSeconds, unsigned int& gpsMicroseconds );

   static void aftrConvertGPSTimeToPTime( const unsigned int& gpsSeconds, const unsigned int& gpsMicroseconds, boost::posix_time::ptime* outPTimeUTC );

   static boost::gregorian::date getGPS_Epoch_boostDate();
   static std::chrono::time_point<std::chrono::system_clock> getGPS_Epoch_chronoDate();

   /// Takes format where a GPS week (Since Jan 6 1980) and a 64-bit floating point value denoting the number of seconds
   /// into that week and returns a boost::posix_time::ptime.
   static boost::posix_time::ptime AftrUtilities::aftrConvert_GPSWeek_GPSSecond_toPTime( int GPSWeek, double GPSSecond );
   static std::chrono::time_point<std::chrono::system_clock> aftrConvert_GPSWeek_GPSSecond_toTimePoint( int GPSWeek, double GPSSecond );

   static std::optional< std::pair< int32_t, double > > aftrConvert_PTime_to_GPSWeek_GPSSecond( boost::posix_time::ptime const& t );
   static std::optional< std::pair< int32_t, double > > aftrConvert_TimePoint_to_GPSWeek_GPSSecond( std::chrono::time_point<std::chrono::system_clock> const& t );

   /// This method converts a std::chrono::system_clock::time_point to a string according to fmt. System resolution is used. On a
   /// Windows 10 Xeon 64 bit machine, this records microsecond precision.
   /// Format options are documented at https://howardhinnant.github.io/date/date.html#to_stream_formatting
   static std::string aftrConvertTimePointToString( const std::chrono::system_clock::time_point& tp, const std::string fmt = "%Y.%b.%d_%H.%M.%S.UTC" );
   
   /// Let's the insertion operator consume a system::clock::time_point and print it to an std::ostream.
   friend std::ostream& operator <<( std::ostream& os, const std::chrono::system_clock::time_point& tp );

   /// This method converts a string to a std::chrono::system_clock::time_point according to fmt. System resolution is used.
   /// On a Windows 10 Xeon 64 bit machine, this deserializes up to microsecond precision.
   /// Format options are documented at https://howardhinnant.github.io/date/date.html#from_stream_formatting
   static std::chrono::system_clock::time_point aftrConvertStringToTimePoint( const std::string& strToParse, const std::string fmt = "%Y.%b.%d_%H.%M.%S.UTC" );

#endif
};


   /*******************************
   Matrix Methods
   *******************************/

   /**
      This method multiplies two column major matrices such that a := a * b. That is,
      "a" accumulates the result of "a" post-multiplied onto "b". This is used
      as multiplication for rotation and scaling manipulations. The two
      matrices MUST BOTH be 4x4 in size. This is used instead of OpenGL's 
      internal methods so this code is ANSI C++ and multi-platform.

      This performs post multiplication using column major indexing.
   */
   template< typename T >
   void multiply4x4Matrix( T a[16], const T b[16] );
   //template void multiply4x4Matrix< float >( float a[16], const float b[16] ); //explicit template instantiation
   //template void multiply4x4Matrix< double >( double a[16], const double b[16] ); //explicit template instantiation

   /**
      This method multiplies two matrices such that result := a * b.
      This performs pre multiplication.
      
      If you'd like to perform the accumulation of two column major
      4x4 matrices (like OpenGL matrices) do the following:
      PV <- P * V, then call (post multiplication of column-major matrices)
      multiply4x4Matrix( V, P, PV ); // PV now stores P * V (post multiplied),
                                     // which is the same as V * P (pre multiplied)
   */
   template< typename T >
   void multiply4x4Matrix( const T a[16], const T b[16], T result[16] );
   //template void multiply4x4Matrix<float>( const float a[16], const float b[16], float result[16] );
   //template void multiply4x4Matrix<double>( const double a[16], const double b[16], double result[16] );

   /**
      Multiplies 4x1 point v by 4x4 matrix a storing the result in 4x1 point out.
   */
   template< typename T >
   void multiply4x4MatrixBy4x1Vector( const T a[16], const T v[4], T out[4] );
   //template void multiply4x4MatrixBy4x1Vector<float>( const float a[16], const float v[4], float out[4] );
   //template void multiply4x4MatrixBy4x1Vector<double>( const double a[16], const double v[4], double out[4] );

   /**
      Returns a column major 4x4 matrix where columns 0, 1, 2 correspond to xdir, ydir, zdir, respectively.
      The 4th column and row are set to 0,0,0,1.
   */
   void make4x4MatrixFrom3Vectors( const Vector& xdir, const Vector& ydir, const Vector& zdir, float m[16] );
   void make3x3MatrixFrom3Vectors( const Vector& xdir, const Vector& ydir, const Vector& zdir, float m[9] );

   /**
      This method finds the 4x4 matrix such that the upper left 3x3 matrix
      is the proper rotation matrix to rotate a point at displacement a from
      the origin to displacement b from the origin and stores it in m. Upper
      left 3x3 described above, m[15] == 0, all remaining elements are 0.
   */
   void determineRotationMatrix( Vector source, Vector destination, float r[16] );

   /**
      This method populates a float[16] from a Vector containing the roll (positive rotation about the X axis),
      pitch (positive rotation about the Y axis), and yaw (positive rotation about the Z axis)
      in the x,y,z components of the Vector, respectively.
   */
   void eulerAnglesToDirectionCosineMatrix( Vector euler, float displayMat[16] );

   /**
      Vector = original * matrix.
      Where Vector is a 3D Aftr Vector, original is the Aftr Vector to be transformed
      by the 4x4 matrix.
   */
   Vector transformVectorThrough4x4Matrix( const Vector& original, const float m[16] );

   /**
      outVec4D = inVec4D * m.
      Where outVec4D and inVec4D correspond to an array of 4 floats. inVec4D is transformed
      by matrix and the result is stored in outVec4D.
   */
   template< typename T >
   void transformVector4DThrough4x4Matrix( const T inVec4D[4], T outVec4D[4], const T m[16] );
   //template void transformVector4DThrough4x4Matrix< float >( const float inVec4D[4], float outVec4D[4], const float m[16] );
   //template void transformVector4DThrough4x4Matrix< double >( const double inVec4D[4], double outVec4D[4], const double m[16] );

    /**
      outVec3D[0..2] = [inVec3D,1] * m.
      Where outVec4D and inVec4D correspond to an array of 4 floats. inVec4D is transformed
      by matrix and the result is stored in outVec4D.
   */
   void transformVector3DThrough4x4Matrix( const float inVec3D[3], float outVec3D[3], const float m[16] );


   /**
      Note: Transposes the elements of the two in passed 4x4 matrices. The inMatrix is
      internally copied to a temporary matrix, so it is completely correct to pass the
      same matrix in as both the in and out matrix - it will still be transposed correctly.
   */
   template< typename T>
   void transpose4x4Matrix( const T inMatrix[], T outMatrix[] );
   //template void transpose4x4Matrix<float>( const float inMatrix[], float outMatrix[] );
   //template void transpose4x4Matrix<double>( const double inMatrix[], double outMatrix[] );

   /**
      Note: Transposes the elements of the two in passed 4x4 matrices. The inMatrix is
      internally copied to a temporary matrix, so it is completely correct to pass the
      same matrix in as both the in and out matrix - it will still be transposed correctly.
   */
   void transpose4x4MatrixD( const double inMatrix[], double outMatrix[] );

   /**
      This method initializes the in passed display matrix to the identity
      matrix.
   */
   template< typename T >
   void aftrSetIdentityMatrix( T matrix[16] );
   //template void aftrSetIdentityMatrix<float>( float matrix[16] );
   //template void aftrSetIdentityMatrix<double>( double matrix[16] );

   std::string print4x4MatrixColumn( float* m );
   std::string print4x4MatrixColumn( double* m );
   std::string print4x4MatrixColumn( float m[4][4] );
   std::string print4x4MatrixRow( float* m );
   std::string print4x4MatrixRow( float m[4][4] );
   std::string printMxNMatrixRow( float* matrix, int m, int n );
   std::string printMxNMatrixRow( float** matrix, int m, int n );

   std::string print4x4MatrixColumnWolframAlpha( double* m );
   std::string print4x4MatrixColumnMatlab( double* m );

   /// Returns the current MODELVIEW_MATRIX on the OpenGL Stack.
   /// This sets the OpenGL MatrixMode to GL_MODELVIEW upon exit.
   std::string printOpenGLMODELVIEWMatrix();

   /// Returns the current PROJECTION_MATRIX on the OpenGL Stack.
   /// This sets the OpenGL MatrixMode to GL_MODELVIEW upon exit.
   std::string printOpenGLPROJECTIONMatrix();


   /*************************************
   End Matrix Methods
   *************************************/

   //if x is a power of 2, return x
   //else return the least greatest power of 2 greater than x
   unsigned int nextPowerOf2( unsigned int x );


   /// Returns the number of OpenGL errors that OpenGL has detected and recorded since the last call to glGetError
   size_t printOpenGLErrors( int i, WO* wo, const std::string& desc );
   size_t printOpenGLErrors( std::string const& desc );
   
   /// Returns a string printing each byte as an integer delimited by spaces
   std::string printBytes( char* dataPtr, unsigned int numBytesToPrint );

   /**
      Removes all leading and trailing non-printable characters. The string that is passed in is
      manipulated. The returned string will begin with a character with an integer value between
      [33,126], if possible. The returned string will end with a character with an integer value 
      between [33,126], if possible.

      Otherwise, an empty string of length 0 will be returned if the string contains only non-printable
      characters.
   */
   void trimStringWhiteSpace( std::string& s );

   /**
   \return Squared distance between point a and point b.
   */
   float computeDistanceSquaredBetween2Points( const Vector& a, const Vector& b );

   /**
   Householder reduction of real, symmetric matrix a[n][n].

   Input - real symmetric matrix a[n-1][n-1]
   Input - n, size of matrix
   Input - d[n-1], storage
   Input - e[n-1], storage

   Output - replaces a by the orthogonal matrix Q effecting the transformation.
   Output - d[n-1] contains diagonal elements
   Output - e[n-1] contains off-diagonal elements (e[0] = 1)

   taken from Numerical Recipes in C
   **/
   void HouseholderReduction(float** a, int n, float d[], float e[]);

   /**
   QL algorithm of a tri-diagonal matrix a[n-1][n-1].

   Input - z, Identity Matrix, or tridiagonal matrix
   Input - d[n-1], main diagonal of symmetric tridiagonal matrix
   Input - e[n-1], off diagnonal of symmetric tridiagonal matrix


   Output - z the eigenvectors with column k corresponding to eigenvalue d[k]
   Output - d the eigenvalues of a

   **/
   void QL(float d[], float e[], int n, float **z);

   /**
   Will generate a 4x4 matrix containing:
   x-basis vector = x
   z-basis vector = the vector in the plane formed by the x and z vectors, orthogonal to x, and in the same direction of z
   y-basis vector = z-basis vector cross x-basis vector
   **/
   void generateMatrixAbsoluteLookGivenUp(Vector x, Vector z, float* m);

   /**
    Will generate a 4x4 matrix containing:
   z-basis vector = z
   x-basis vector = the vector in the plane formed by the x and z vectors, orthogonal to z, and in the same direction of x
   y-basis vector = z-basis vector cross x-basis vector
   **/
   void generateMatrixAbsoluteUpGivenLook(Vector z, Vector x, float* m);

   /**
   returns the matrix generated by the given row * the given column - the user owns the memory returned from this function
   and must delete it themselves
   **/
   Matrix columnTimesRow( const std::vector<float>& column, const std::vector<float>& row );
   void columnTimesRow( const std::vector<float>& column, const std::vector<float>& row, Matrix& m );

   /**
      This method is an exact reimplementation of gluLookAt. This exists because Open GL 1.1
      ES does not have a glu library implemented. Hence the Aftr class re implements this method.
      Usage of this function should be used identically to gluLookAt. That is, one can simply
      replace all calls to GLU's gluLookAt with aftrGluLookAt, of course, the eye, center, and
      up parameters use the Aftr Engine's Vector class instead of passing 9 floats.


      gluLookAt creates a viewing matrix derived from an eye point, a reference point indicating the
      center of the scene, and an UP vector.

      The matrix maps the reference point to the negative z axis and the eye point to the origin. When
      a typical projection matrix is used, the center of the scene therefore maps to the center of the viewport. Similarly,
      the direction described by the UP vector projected onto the viewing plane is mapped to the
      positive y axis so that it points upward in the viewport. The UP vector
      must not be parallel to the line of sight from the eye point to the reference point.
   */
   void aftrGluLookAt( const Vector& eye, const Vector& center, const Vector& up );

   /**
      Helper method called by aftrGluLookAt. Populates the output 4x4 matrix to the current
      Open GL View Matrix. This method does not modify any OpenGL state.
   */
   void aftrComputeViewMatrix( const Vector& eye, const Vector& center, const Vector& up, float* out4x4ViewMatrix );

   /**
      This method is an exact reimplementation of gluPerspective. This exists because Open GL 1.1
      ES does not have a glu library implemented. Hence the Aftr reimplements this method.
      Usage of this function should be used identically to gluPerspective. That is, one can simply
      replace all calls to GLU's gluPerspective with aftrGluPerspective.

      This will accumulate the calculated projection matrix into the current matrix. Typically, the
      user would do something like:
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      aftrGluPerspective( fovyInDegrees, aspect, zNear, zFar );
      glMatrixMode( GL_MODELVIEW );
      ...

      gluPerspective specifies a viewing frustum into the world coordinate system.
      In general, the aspect ratio in gluPerspective should match the aspect ratio
      of the associated viewport. For example, aspect = 2.0 means  the viewer's
      angle of view is twice as wide in x as it is in y.
      If the viewport is twice as wide as it is tall, it displays the image without distortion.

      The matrix generated by gluPerspective is multiplied by the current matrix,
      just as if glMultMatrix were called with the generated matrix.
      To load the perspective matrix onto the current matrix stack instead,
      precede the call to gluPerspective with a call to glLoadIdentity.
        
   */
   void aftrGluPerspective( float fovyInDegrees, float aspect, float zNear, float zFar );
   
   /**
      Identical to aftrGluPerspective with one exception - instead of manipulating the current OpenGL
      state (via glMultMatrixf(projMat)), the computed perspective projection matrix is returned 
      via the outProjectionMatrix parameter.
      
      This method is used by the camera to update its perspective projection matrix without changing 
      any OpenGL state.
   */
   void aftrGluPerspectiveNoGLStateModification( float fovyInDegrees, float aspect, float zNear, float zFar, float outProjectionMatrix[] );

   /**
      Inverts a 4x4 matrix by pivoting on largest element in column, returns false if matrix is singular.
   */
   template< typename T >
   bool aftrGluInvertMatrix(const T src[16], T inverse[16]);
   //template bool aftrGluInvertMatrix< float >( const float src[16], float inverse[16] );
   //template bool aftrGluInvertMatrix< double >( const double src[16], double inverse[16] );
   //int aftrGluInvertMatrixd(const double src[16], double inverse[16]);

   /**
      Creates a projection matrix that can be used to restrict drawing to a small region of the viewport.
      This is typically useful to determine what objects are being drawn near the cursor.
      x,y - Specify the center of a picking region in window coordinates.
      width, height - Specify the width and height, respectively, of the picking region in window coordinates.
      viewport - Specifies the current viewport.
         viewport[0,1]=x,y - Specify the lower left corner of the viewport rectangle, in pixels.
         viewport[2,3]=width,height - Specify the width and height of the viewport, in pixels.

   */
   template< typename T > Mat4T<T> aftrGluPickMatrix( T x, T y, T width, T height, int viewport[4] );
   //template Mat4T<float> aftrGluPickMatrix<float>( float x, float y, float width, float height, int viewport[4] ); //explicit template instantiation
   //template Mat4T<double> aftrGluPickMatrix<double>( double x, double y, double width, double height, int viewport[4] ); //explicit template instantiation

   template< typename T >
   bool aftrGluUnProject( T winx, T winy, T winz, const T modelViewMatrix[16], const T projMatrix[16], const int viewport[4], 
                         T* objSpaceX, T* objSpaceY, T* objSpaceZ );
   //template bool aftrGluUnProject<float>( float winx, float winy, float winz, const float modelViewMatrix[16], const float projMatrix[16], const int viewport[4], float* objSpaceX, float* objSpaceY, float* objSpaceZ );
   //template bool aftrGluUnProject< double >( double winx, double winy, double winz, const double modelViewMatrix[16], const double projMatrix[16], const int viewport[4], double* objSpaceX, double* objSpaceY, double* objSpaceZ );

   void aftrGluOrtho2D( float left, float right, float bottom, float top );

   /**
      Identical to aftrGluOrtho2D with one exception - instead of manipulating the current OpenGL
      state (via glMultMatrixf(projMat)), the computed perspective projection matrix is returned 
      via the outProjectionMatrix parameter.
      
      This method is used by the camera to update its perspective projection matrix without changing 
      any OpenGL state.

      A common set of input parameters would be left=0, right=1, bottom=0, top=1, near=-1, far=1.
   */
   void aftrGluOrtho2DNoGLStateModification( float left, float right, float bottom, float top, float near, float far, float outProjectionMatrix[] );
  
   /**
      Strips the leading path information and returns only the file name.
      For example input path: "../../../shared/mm/images/DefaultTexture.bmp"
      becomes "DefaultTexture.bmp".

      This method assumes "/" is the directory delimiter, "\" does NOT work.
      If no "/" is found, the input string will be returned as the output.
   */
   std::string aftrRemoveLeadingPathFromFileName( const std::string& fileName );

   /**
      This function expects a 3 column matrix and returns a pointer to a vector of Vector*
      which the caller owns.
   */
   std::vector<Vector*>* convertMatrixToVectorOfPoints( Matrix& m );

   /**
      Returns the intersection point between the infinite ray formed by rayTail to rayHead
      and the in passed plane. If parametricDistanceT is not NULL, the parametric value
      t in the range [0,1] will be returned as well.

      returns AftrGeometricTerm::geoSUCCESS if an intersection is discovered
      returns AftrGeometricTerm::geoPARALLEL if no intersection occurs
      returns AftrGeometricTerm::geoCOPLANAR if the lines lies in the plane
      returns AftrGeometricTerm::geoOUTSIDE if using lineSegment and the segment will not intersect the plane
   */
   AftrGeometricTerm intersectLinePlane( const Vector& rayTail, const Vector& rayHead, 
                                            const AftrGeometryPlane& plane, Vector& output,
                                            bool isLineSegment, float* parametricDistanceT = NULL );

   /**
      Returns the intersection point between the infinite ray formed by rayTail to rayHead
      and the in passed plane. This works in N dimensions.

      returns AftrGeometricTerm::geoSUCCESS if an intersection is discovered
      returns AftrGeometricTerm::geoPARALLEL if no intersection occurs
      returns AftrGeometricTerm::geoCOPLANAR if the lines lies in the plane
      returns AftrGeometricTerm::geoOUTSIDE if using lineSegment and the segment will not intersect the plane
   */
   AftrGeometricTerm intersectLinePlane( const std::vector< double >& rayTail,
                                            const std::vector< double >& rayHead, 
                                            const std::vector< double >& nDimPointInPlane,
                                            const std::vector< double >& nDimPlaneNormal,
                                            std::vector< double >& output,
                                            bool isLineSegment );

   /**
      Performs an intersection test between an Axis Aligned Bounding Box (of dimensions AABBLxLyLz)
      and the vector formed by rayHead - rayTail. The Axis Aligned Bounding Box (AABB) is assumed
      to be centered at (0,0,0); as a result, the center position of the "actual" bounding box
      must be subtracted from the rayTail and rayHead prior to invoking this method.

      For example, assume rayTail is (1,2,0) and rayHead is (2,1,0) and the AABB is 
      supposed to be centered at (1,1,0). Then prior to invoking this method, subtract
      the AABB center position from both the rayTail and rayHead:

      transformedRayTail = rayTail - (1,1,0) //(1,1,0) is the AABB's center position
      transformedRayHead = rayHead - (1,1,0) //(1,1,0) is the AABB's center position
      
      //Test for intersection
      result = intersectLineAABB( transformedRayTail, transformedRayHead, ... )

      There are several cases that can occur when intersecting a ray with an AABB.
      -1 The ray is completely contained within the AABB (returns AftrGeometricTerm::geoINSIDE,
         sets foundEntryPoint and foundExitPoint to false,
         sets entryPoint to rayTail and exitPoint to rayHead)

      -2 The ray is completely outside the AABB (returns AftrGeometricTerm::geoOUTSIDE,
         sets foundEntryPoint and foundExitPoint to false))

      -3 The rayTail begins outside the AABB, passes into the AABB, 
         and the rayHead ends inside the AABB. (returns AftrGeometricTerm::geoSUCCESS, 
         populates entryPoint with the point of entry, sets foundEntryPoint to true,
         sets foundExitPoint to false, sets exitPoint to rayHead).

      -4 The rayTail begins outside the AABB, passes through the AABB, 
         and the rayHead ends outside the AABB. (returns AftrGeometricTerm::geoSUCCESS,
         populates entryPoint with the point of entry and populates 
         exitPoint with the point of exit. Sets foundEntryPoint and foundExitPoint
         to true).

      -5 The rayTail begins inside the AABB and the rayHead lies outside the AABB.
         (returns AftrGeometricTerm::geoSUCCESS, sets exitPoint to the point of exit, sets foundExitPoint
         to true and sets foundEntryPoint to false, sets entryPoint to rayTail).

      -6 The ray just touches the AABB at a single point (corner). (returns AftrGeometricTerm::geoSUCCESS,
         sets entryPoint and exitPoint to the contact point, sets foundEntryPoint and
         foundExitPoint to true).
   */
   AftrGeometricTerm intersectLineAABB( const Vector& rayTail, const Vector& rayHead, 
      const Vector& AABBLxLyLz, Vector& entryPoint, Vector& exitPoint, bool& foundEntryPoint,
      bool& foundExitPoint, bool isLineSegment );

   /**
      returns true if point is inside the triangle formed by a, b, and c
      returns false otherwise
   */
   bool isInsideTriangle( const Vector& point, const Vector& a, const Vector& b, const Vector& c);

   /**
      This method is a helper method used by intersectLineAABB(...). Given a point, the
      rectangle's 2 side lengths (passed in via lxlylz), and the normal direction, this method
      returns true iff the point is in the rectangle. lxlylz represent exactly half the length of
      the rectangle's x,y,z dimensions.
      The 2 values used from the in passed lxlylz are a function of what the normal direction is.

      Assume the viewer is at the origin looking along the +x axis, with the normal being the +z,
      and the +y being to the left.

      Valid normalDirection values:
      0 is "front face"  -> (Normal Direction is (1,0,0))
      1 is "right face"  -> (Normal Direction is (0,-1,0))
      2 is "back face"   -> (Normal Direction is (-1,0,0))
      3 is "left face"   -> (Normal Direction is (0,1,0))
      4 is "bottom face" -> (Normal Direction is (0,0,-1))
      5 is "top face"    -> (Normal Direction is (0,0,1))

      For example, if the "front face" of a rectangle (Y dim is 15.0, Z dim is 20.0) needs to 
      see if point R lies inside of it, then one invokes:
      bool isInside = isInsideAxisAlignedRectangle(R, Vector(0, 15.0f/2.0f, 20.0f/2.0f), 0);

      This method may not be particularly useful for general use, as it was written as a quick
      helper to accelerate intersectLineAABB(...).

      Returns true iff the point is within the rectangle; false, otherwise.
   */
   bool isInsideAxisAlignedRectangle( const Vector& pt, const Vector& lxlylz, unsigned int normalDirection );

   /**
      returns true if any part of triangle 'tri' is may be contained within the boundary, or on the boundary, of
      the rectangular prism 'prism'. Variable 'prism' must be an array of 6 AftrPlanes; these planes
      are the 6 faces forming the rectangular prism. Furthermore, each normal must point OUT FROM the
      center of the rectangular prism (the normal of each face must point away from the center of the prism).

      This method is not exactly accurate, it may return false positives; that is, this function may return
      true even if the triangle is not necessarily inside this prism. This method, however, will never return
      a false negative; that is, this method will never return false, when the triangle may be contained by the
      prism. This is done for computation efficiency reasons and is a good trade off between efficiency and
      accuracy if this method is used to populated acceleration structures such as octrees.

      This function performs the following using at minimum 3 dot products, or at most, 18 dot
      products:
      As long as at least any one point of the triangle is "inside" all six faces of the prism
      true is returned, false otherwise.

      returns false if no part of the triangle is contained within the rectangular prism.
   */
   //SLN Reminder: I think this method ALWAYS returns true... need to test this...
   bool isPossiblyInsideRectangularPrism( const AftrGeometryTriangleIndexed& tri, const AftrGeometryPlane prism[] );

   /**
      Returns true if pt lies inside the rectangular prism; false, otherwise.

      Variable 'prism' must be an array of 6 AftrPlanes; these planes
      are the 6 faces forming the rectangular prism. Furthermore, each normal must point OUT FROM the
      center of the rectangular prism (the normal of each face must point away from the center of the prism).
   */
   bool isInsideRectangularPrism( const Vector& pt, const AftrGeometryPlane prism[] );

   /**
      Tests if an Axis aligned bounding box intersects with an arbitrarily oriented bounding box.
      This uses the separating axis test internally, at most requiring a 3x3 matrix mult and
      15 dot products/crossproducts.
      Returns true iff the AABB and OBB intersect; false, otherwise.
   */
   bool intersectAABBagainstOBB( const AftrGeometryAABB& a, const AftrGeometryOBB& b );

   /**
      Tests if an arbitrarily oriented bounding box intersects with another arbitrarily oriented bounding box.
      This uses the separating axis test internally, at most requiring a 3x3 matrix mult and
      15 dot products/crossproducts.
      Returns true iff the AABB and OBB intersect; false, otherwise.
   */
   bool intersectOBBagainstOBB( const AftrGeometryOBB& a, const AftrGeometryOBB& b );

   /**
      Returns true iff, the AABB intersects the frustum; false, otherwise.
   */
   bool intersectFrustumAgainstAABB( const AftrGeometryFrustum& f, const AftrGeometryAABB& b );

   /**
      Returns truee iff, the OBB intersects the frustum; false, otherwise.
   */
   bool intersectFrustumAgainstOBB( const AftrGeometryFrustum& f, const AftrGeometryOBB& b );


   /// Returns ture if x is within epsilon of 0, returns false otherwise.
   /// Epsilon = .0001;
   bool isFloatZero(float x );

   /// Returns true if x is within epsilon of 0; false, otherwise.
   /// Epsilon is user defined as the second parameter.
   bool isFloatZero(float x, float epsilon );

   /// Returns ture if x is within epsilon of 0, returns false otherwise.
   /// Epsilon = .000001;
   bool isFloatZero(double x );

   /// Returns true if x is within epsilon of 0; false, otherwise.
   /// Epsilon is user defined as the second parameter.
   bool isFloatZero(double x, double epsilon );
   
   /// Returns true if float x is within epsilon of float y; false, otherwise.
   bool isFloatEqual( float x, float y, float epsilon );

   //float debugging
   bool isFinite( float x );
   bool isNotNaN( float x );
   bool isValid( float x );

   /// Returns the N-dimensional dot product between vector a and b.
   double dotProduct( const std::vector< double >& a, const std::vector< double >& b );

   /// Normalizes the in passed vector
   void normalizeVector( std::vector< double >& toNormalize );

   /// Returns the magnitude of the in passed 
   double magnitudeOfVector( const std::vector< double >& vec );

   /// Returns the magnitude squared of the in passed vector
   double magnitudeSquaredOfVector( const std::vector< double >& vec );

   ///Multiplies each component of the vector by scaleFactor
   void scaleVector( std::vector< double >& vec, double scaleFactor );

   /// Returns the sum of the component-wise addition of a + b.
   std::vector< double > sumVector( const std::vector< double >& a, const std::vector< double >& b );

   /// Returns the difference of the component-wise addition of a - b.
   std::vector< double > subtractVector( const std::vector< double >& a, const std::vector< double >& b );

   /// Splits string 'toSplit' at each occurence of any string delimiter specified in 'delimiters' vector of strings.
   /// Each split substring is inserted into its own string in the returned vector of strings.
   std::vector< std::string > splitString( const std::string& toSplit, const std::vector< std::string >& delimiters );

   /// Splits string 'toSplit' at each occurence of any character specified in the 'delimiters' string.
   /// Each split substring is inserted into its own string in the returned vector of strings.
   std::vector< std::string > splitString( const std::string& toSplit, const std::string& delimiters );

   /// returns the first power of 2 >= x
   int aftrNextPowerOf2( int x );

   /**
      Given a pixel location (x,y), convert this to a floating point value in OpenGL screen coordinates.
      That is, (0,0) is the lower left corner of the screen and (1,1) is the upper right corner of the
      screen. The current screen resolution is used when converting pixel location to floating point
      values.
      The first element of the pair is the x coordinate, and the second element of the pair is the
      y coordinate.

      This computation is based off of the ManagerWindowing::getWindowWidth/Height()... This method is
      used for GUI computations. To convert from World Space to Screen Space, use 
      AftrCoordinateTransforms...
   */
   std::pair< float, float > convertPixelCoordToOpenGLScreenCoord( int x, int y );

   ///returns the luminance (gray-scale) value for a given RGB value
   double convertRGBtoLuminance( const Vector& rgb );
   double convertRGBtoLuminance( unsigned char red, unsigned char green, unsigned char blue );


   /**
   //Image comparison Metrics
   **/

   /// Computes RMS Luminance difference between image a and image b. A and B must be the same size and 
   /// their bytes per pixel must match
   float calculateRMSLuminanceDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b );
   float calculateRMSLuminanceDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2 );

   /// "Haar Wavelet" style comparison using Mipmaps
   float calculateWeightedMipmapDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b );
   float calculateWeightedMipmapDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2 );

   std::vector< int > generateColorHistogram( size_t width, size_t height, size_t bpp, unsigned char* bytes, int rangeMin, int rangeMax);

   /**
   Shrinks a 32bit or 8bit 'src' surface ti a newly created 'dst' surface.
   'factorx' and 'factory' are the shrinking ratios (i.e. 2=1/2 the size,
   3=1/3 the size, etc.) The destination surface is antialiased by averaging
   the source box RGBA or Y information. If the surface is not 8bit
   or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.

   SLN: I 'stole' this code from SDL_gfx Library
   http://www.ferzkopp.net/joomla/content/view/19/14/

   I did this to avoid having to build yet another library to link against on all
   the platforms this functionality is needed.
   */
   void aftrShrinkSDLSurfaceRGBA( SDL_Surface* src, SDL_Surface* dst, int factorx, int factory );

   /**
   Bilinear interpolates SDL_Surface src to resize a destination surface to dstPixelWidth by
   dstPixelHeight pixels. The destination surface is allocated within this method and returned.
   After being returned, the user is responsible for calling SDL_FreeSurface(...) on the
   generated destination surface.

   \return A new SDL_Surface representing a resized src surface. This is owned by the user
   and the user is responsible for destroying it.
   */
   SDL_Surface* aftrResizeSDLSurfaceRGBA( SDL_Surface* src, unsigned int dstPixelWidth, unsigned int dstPixelHeight );

   /**
   Assigns a topology of indices for the Delaunay triangulation of the given vertices, "vertices," to "topology."
   */
   void aftrGenerateDelaunayTriangulationForVertices( const std::vector< Vector >& vertices, std::vector< unsigned int >& topology );

   void aftrBilinearInterpolation( SDL_Surface* src, tColorRGBA* outData, float x, float y );

   //bilinear interpolation
   //q11 - min x, min y
   //q12 - min x, max y
   //q21 - max x, min y
   //q22 - max x, max y
   double aftrBilinearInterpolation( double q11, double q12, double q21, double q22, double x, double xmin, double xmax, double y, double ymin, double ymax ); 
   double aftrLinearInterpolation( double location1, double value1, double location2, double value2, double locationToFindValueFor );
   double aftrUnlinearInterpolation( double location1, double value1, double location2, double value2, double valueToFindLocationFor );

} //namespace Aftr
