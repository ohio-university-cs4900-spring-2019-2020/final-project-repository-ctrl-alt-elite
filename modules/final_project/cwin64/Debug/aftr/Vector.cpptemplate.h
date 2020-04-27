
namespace Aftr
{

template< typename T >
VectorT<T>::VectorT( )
{   
   x = 0.0;
   y = 0.0;
   z = 0.0;

   static_assert( sizeof( VectorT<T> ) == sizeof( T ) * 3,
                  "Aftr Compiler Halt: VectorT<T> MUST not change its size of 3*T.\n" \
                  "This would cause float* xyz to have a different layout than std::vector<VectorT<float>>.\n" \
                  "This would ultimately hurt performance." );
}

template< typename T >
VectorT<T>::VectorT( T v[] )
{
   this->x = v[0];
   this->y = v[1];
   this->z = v[2];
}

template< typename T >
VectorT<T>::VectorT( const VectorT<T>& v )
{
   *this = v;
}

template< typename T >
VectorT<T>::VectorT( const VectorT<T>* vectorToBeCopied )
{
   if(vectorToBeCopied != NULL)
   {
      this->x = vectorToBeCopied->x;
      this->y = vectorToBeCopied->y;
      this->z = vectorToBeCopied->z;
   }
   else
   {
      this->x = this->y = this->z = 0;
   }
}

template< typename T >
VectorT<T>::VectorT( T x, T y, T z )
{
   this->x = x;
   this->y = y;
   this->z = z;
}

template< typename T >
VectorT<T>::VectorT( T xyz )
{
   this->x = xyz;
   this->y = xyz;
   this->z = xyz;
}

template< typename T >
VectorT<T>::VectorT( const std::string& str )
{
   //This regex matches a Ting point number (RegEx explained at http://www.regular-expressions.info/Tingpoint.html)
   std::string regEx = "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?";
   std::vector< std::string > vals( 3, "0" );
   #ifdef AFTR_CONFIG_USE_BOOST
   {
      boost::sregex_iterator i( str.begin(), str.end(), boost::regex( regEx ) );
      boost::sregex_iterator end;

      size_t count = 0;
      while( i != end && count <= 3 )
      {
         vals[count] = i->str();
         ++i; ++count;
      }
   }
   #else
      std::cout << "WARNING: AFTR_CONFIG_USE_BOOST is not defined - no regEx to parse VectorT( const std::string& ) - will return (0,0,0)..." << AFTR_FILE_LINE_STR << std::endl;
   #endif

   if( vals.size() >= 3 )
   {
      std::stringstream ss;
      ss << vals[0] << " " << vals[1] << " " << vals[2];

      ss >> this->x;
      ss >> this->y;
      ss >> this->z;
   }
   else
   {
      std::cout << "WARNING!!! VectorT<T>::VectorT<T>( const std::string& str ), could not match 3 Ting point values, setting VectorT<T> to zero...\n";
   }
}

template< typename T >
VectorT<T>::VectorT( std::vector< float >& v )
{
   this->x = 0;
   this->y = 0;
   this->z = 0;

   for( size_t i = 0; i < 3 && i < v.size(); ++i )
      this->at(i) = v[i];
}

template< typename T >
VectorT<T>::VectorT( std::vector< double >& v )
{
   this->x = 0;
   this->y = 0;
   this->z = 0;

   for( size_t i = 0; i < 3 && i < v.size(); ++i )
      this->at(i) = (T) v[i];
}

template< typename T >
void VectorT<T>::clear()
{
   this->x = 0;
   this->y = 0;
   this->z = 0;
}

//template< typename T >
//VectorT<T> VectorT<T>::operator +( const VectorT<T>& v ) const
//{
//   return VectorT<T>( this->x + v.x, this->y + v.y, this->z + v.z );
//}

template< typename T >
VectorT<T> VectorT<T>::operator +( const T& d ) const
{
   return VectorT<T>( this->x + d, this->y + d, this->z + d );
}

template< typename T >
VectorT<T> VectorT<T>::operator -( const VectorT<T>& v ) const
{
   return VectorT<T>( this->x - v.x, this->y - v.y, this->z - v.z );
}

template< typename T >
VectorT<T> VectorT<T>::operator -( const T& d ) const
{
   return VectorT<T>( this->x - d, this->y - d, this->z - d );
}

template< typename T >
VectorT<T> VectorT<T>::operator *( const VectorT<T>& v ) const
{
   return VectorT<T>( this->x * v.x, this->y * v.y, this->z * v.z );
}

template< typename T >
VectorT<T> VectorT<T>::operator *=( const VectorT<T>& v)
{
   this->x *= v.x;
   this->y *= v.y;
   this->z *= v.z;

   return *this;
}

template< typename T >
VectorT<T> VectorT<T>::operator *( const T& d ) const
{
   return VectorT<T>( this->x * d, this->y * d, this->z * d );
}

template< typename T >
VectorT<T> VectorT<T>::operator *=( const T& d )
{
   this->x *= d;
   this->y *= d;
   this->z *= d;

   return *this;
}

template< typename T >
VectorT<T> VectorT<T>::operator /( const VectorT<T>& v)const
{
   return VectorT<T>( this->x / v.x, this->y / v.y, this->z / v.z );
}

template< typename T >
VectorT<T> VectorT<T>::operator /( const T& d)const
{
   return VectorT<T>( this->x / d, this->y / d, this->z / d );
}

template< typename T >
VectorT<T> VectorT<T>::operator /=( const VectorT<T>& v)
{
   this->x /= v.x;
   this->y /= v.y;
   this->z /= v.z;

   return *this;
}

template< typename T >
VectorT<T> VectorT<T>::operator /=( const T& d)
{
   this->x /= d;
   this->y /= d;
   this->z /= d;

   return *this;
}

template< typename T >
VectorT<T> VectorT<T>::operator +=( const VectorT<T> &v )
{
   this->x += v.x;
   this->y += v.y;
   this->z += v.z;

   return *this;
}

template< typename T >
VectorT<T> VectorT<T>::operator -=( const VectorT<T> &v )
{
   this->x -= v.x;
   this->y -= v.y;
   this->z -= v.z;

   return *this;
}

template< typename T >
VectorT<T>* VectorT<T>::minus( VectorT<T>* v ) const
{
   //Ensure we are substracting two different vectors
   if( this != v )
   {
      VectorT<T>* diff = new VectorT<T>();

      diff->x = x - v->x;
      diff->y = y - v->y;
      diff->z = z - v->z;

      return diff;
   }
   else
   {
      //we are substracting one vector from itself since (this == v).
      //thus we return zero.
      return new VectorT<T>( 0.0, 0.0, 0.0 );
   }
}

template< typename T >
void VectorT<T>::operator =( VectorT<T>* v )
{
   //ensure we are assigning one vector equal to another
   //vector.  Otherwise, the vector is already equal to itself.
   if (v == nullptr)//should check for NULL first, unless we actually want this behavior to represent a 0,0,0 vector or something?
   {
      std::cout << "Assigning a vector to a NULL vector is bad." << std::endl;
   }
   else if( this != v )
   {
      x = v->x;
      y = v->y;
      z = v->z;
   }
  
}

template< typename T >
VectorT<T>& VectorT<T>::operator =( const VectorT<T>& v )
{
   if( this != &v )
   {
      x = v.x;
      y = v.y;
      z = v.z;
   }
   return *this;
}

template< typename T >
bool VectorT<T>::operator ==( const VectorT<T>& v ) const
{
   if( fabs( this->x - v.x ) < ZERO_THRESHOLD() &&
       fabs( this->y - v.y ) < ZERO_THRESHOLD() &&
       fabs( this->z - v.z ) < ZERO_THRESHOLD() )
   {
      return true;
   }

   return false;
}

template< typename T >
bool VectorT<T>::operator !=( const VectorT<T>& v ) const
{
   if( (*this) == v )
      return false;
   return true;
}

template< typename T >
bool VectorT<T>::operator < (const VectorT<T> & v) const
{
   T a = this->magnitudeSquared();
   T b = v.magnitudeSquared();

   if( fabs( a - b ) <= 0.0001f )
   {
      if( this->x < v.x )
         return true;
      else if( this->x > v.x )
         return false; //now this->x == v.x, implicitly
      else if( this->y < v.y )
         return true;
      else if( this->y > v.y )
         return false; //now this->y == v.y, implicitly
      else if( this->z < v.z )
         return true;
      else if( this->z > v.z )
         return false; //now this->z == v.z, implicitly
      else
         return false; //the two Vectors are implicitly equal
   }
   else if( a < b )
      return true;
   else
      return false;
}

template< typename T >
bool VectorT<T>::operator > (const VectorT<T> & v) const
{
   if( magnitudeSquared() > v.magnitudeSquared() )
      return true;
   else
      return false;
}

template< typename T >
T& VectorT<T>::operator [] ( size_t i )
{
   if(i == 0)
      return x;
   if(i == 1)
      return y;
   if(i == 2)
      return z;
   //ERROR, replace with exception at some point
   std::cout << " User attempted to access a component outside the interval [0,2].  Exiting. " << std::endl;
   std::cin.get();
   exit(-1);
}

template< typename T >
T VectorT<T>::operator [] ( size_t i ) const
{
   if(i == 0)
      return x;
   if(i == 1)
      return y;
   if(i == 2)
      return z;
   //ERROR, replace with exception at some point
   std::cout << " User attempted to access a component outside the interval [0,2].  Exiting. " << std::endl;
   std::cin.get();
   exit(-1);
}

template< typename T >
T& VectorT<T>::at( size_t i )
{
   if(i == 0)
      return x;
   if(i == 1)
      return y;
   if(i == 2)
      return z;
   //ERROR, replace with exception at some point
   std::cout << " User attempted to access a component outside the interval [0,2].  Exiting. " << std::endl;
   std::cin.get();
   exit(-1);
}

template< typename T >
T VectorT<T>::at( size_t i ) const
{
   if(i == 0)
      return x;
   if(i == 1)
      return y;
   if(i == 2)
      return z;
   //ERROR, replace with exception at some point
   std::cout << " User attempted to access a component outside the interval [0,2].  Exiting. " << std::endl;
   std::cin.get();
   exit(-1);
}

template< typename T >
bool VectorT<T>::isEqual( const VectorT<T>& v, T tolerance ) const
{
   if( fabs( this->x - v.x ) <= tolerance &&
      fabs( this->y - v.y ) <= tolerance &&
      fabs( this->z - v.z ) <= tolerance )
      return true;
   else
      return false;
}

template< typename T >
bool Aftr::VectorT<T>::isValidForEachComponent() const
{
#ifdef AFTR_CONFIG_USE_BOOST

   if( !boost::math::isinf( this->x ) && !boost::math::isnan( this->x ) &&
       !boost::math::isinf( this->y ) && !boost::math::isnan( this->y ) &&
       !boost::math::isinf( this->z ) && !boost::math::isnan( this->z ) )
      return true;
   return false;

#else
   std::cout << "VectorT<T>::isValidForEachComponent(): WARNING: boost not used,\n"
      << "   resorting to potentially non-portable usage:\n"
      << "   return( x == x && y == y && z == z );\n";
   return( x == x && y == y && z == z );

#endif
}

template< typename T >
VectorT<T>* VectorT<T>::crossProduct( VectorT<T>* v ) const
{
   //       | X   Y   Z
   //a x b =| a1  a2  a3
   //       | b1  b2  b3
   //
   //a x b = (a2b3 - a3b2)i + (a3b1 - a1b3)j + (a1b2 - a2b1)k 

   VectorT<T>* cross = new VectorT<T>();

   cross->x = y * v->z - z * v->y;
   cross->y = z * v->x - x * v->z;
   cross->z = x * v->y - y * v->x;

   return cross;
}

template< typename T >
VectorT<T> VectorT<T>::crossProduct( const VectorT<T>& v ) const
{
   VectorT<T> cross;

   cross.x = y * v.z - z * v.y;
   cross.y = z * v.x - x * v.z;
   cross.z = x * v.y - y * v.x;

   //v.x = ( y * v2.z )  ( z * v2.y );
   //v.y = ( z * v2.x )  ( x * v2.z );
   //v.z = ( x * v2.y )  ( y * v2.x );

   return cross;
}

template< typename T >
T VectorT<T>::dotProduct( VectorT<T>* v ) const
{
   //A(.)B = A.x * B.x + A.y * B.y + A.z * B.z
   return( x * v->x + y * v->y + z * v->z );
}

template< typename T >
T VectorT<T>::dotProduct( const VectorT<T>& v ) const
{
   //A(.)B = A.x * B.x + A.y * B.y + A.z * B.z
   return( x * v.x + y * v.y + z * v.z );
}

template< typename T >
VectorT<T> VectorT<T>::vectorProjectOnto( const VectorT<T>& v ) const
{
   VectorT<T> vNorm = v.normalizeMe();
   VectorT<T> meProjOntoV = vNorm * ( this->dotProduct( vNorm ) );
   return meProjOntoV;
}

template< typename T >
T VectorT<T>::scalarProjectionOnto( const VectorT<T>& v ) const
{
   //VectorT<T> vNorm = v.normalizeMe();
   //T scalarProj = this->dotProduct( vNorm );
   //return scalarProj;

   T scalarProj = this->dotProduct( v ) / v.magnitude();
   return scalarProj;

}

template< typename T >
VectorT<T> VectorT<T>::vectorProjectOnToPlane( const VectorT<T>& planeNormal ) const
{
   //Project this vector onto the plane's normal vector, then subtract the
   //result from this vector, yeilding a vector within the plane defined by planeNormal
   //Easy projection, just drop z component and renormalize...
   //U = V - (V dot N)N
   VectorT<T> v = *this;
   VectorT<T> proj = v - ( planeNormal * ( v.dotProduct( planeNormal ) ) );
   return proj;
}

template< typename T >
void VectorT<T>::normalize()
{
   //Normalize a vector by dividing the x, y, and z 
   //components by the vector's magnitude.

   T mag = this->magnitude();

   if( fabs( mag ) - .00001 < 0 )
   {
      //VectorT<T> is (0,0,0)
      //std::cout << "WARNING: Normalized zero VectorT<T>...\n";
      return; //we define a vector of (0,0,0) that is normalized to remain (0,0,0)
   }

   x /= mag;
   y /= mag;
   z /= mag;
}

template< typename T >
VectorT<T> VectorT<T>::normalizeMe() const
{
   T mag = this->magnitude();
   if( mag  - .00001 < 0 )
      return VectorT<T>(0,0,0);

   VectorT<T> n( x/mag, y/mag, z/mag );
   return n;
}

template< typename T >
T VectorT<T>::magnitude() const
{
   //|Magnitude| = sqrt(x^2 + y^2 +z^2)
   return( sqrt( x * x + y * y + z * z ) );
}

template< typename T >
T VectorT<T>::magnitudeSquared() const
{
   return( x * x + y * y + z * z );
}

template< typename T >
T VectorT<T>::distanceFrom(const VectorT<T> & v) const
{
   return VectorT<T>(v.x - x, v.y - y, v.z - z).magnitude();
}

template< typename T >
// rotates about y axis by phi, then about z axis by theta
VectorT<T> VectorT<T>::rotate(T phi, T theta) const
{
   T xp, yp, zp;

   xp = x * cos(phi) * cos(theta) - y * sin(theta) + z * cos(theta) * sin(phi);
   yp = x * cos(phi) * sin(theta) + y * cos(theta) + z * sin(phi) * sin(theta);
   zp = -x * sin(phi) + z * cos(phi);

   return VectorT<T>(xp, yp, zp);
}

template< typename T >
// rotates about an arbitrary vector
VectorT<T> VectorT<T>::rotate(const VectorT<T> & rotVector, T angle) const
{
   // this uses equations derived by Glenn Murray at the Colorado
   // School of Mines.  See the file doc/ArbitraryAxisRotation for a
   // description of how this works.

   VectorT<T> normalizedRotVector;
   T u, v, w;
   T xp, yp, zp;

   // normalize the vector <u, v, w> about which to rotate
   // this simplifies the calculations in the next section because
   // sqrt(u*u + v*v + w*w) == 1 and (u*u + v*v + w*w) == 1
   normalizedRotVector = rotVector;
   normalizedRotVector.normalize();

   u = normalizedRotVector.x;
   v = normalizedRotVector.y;
   w = normalizedRotVector.z;

   xp = u * (u * x + v * y + w * z) +
      (x * (v*v + w*w) - u * (v * y + w * z)) * cos(angle) +
      (v * z - w * y) * sin(angle);
   yp = v * (u * x + v * y + w * z) +
      (y * (u*u + w*w) - v * (u * x + w * z)) * cos(angle) +
      (w * x - u * z) * sin(angle);
   zp = w * (u * x + v * y + w * z) +
      (z * (u*u + v*v) - w * (u * x + v * y)) * cos(angle) +
      (u * y - v * x) * sin(angle);

   return VectorT<T>(xp, yp, zp);
}

template< typename T >
VectorT<T> Aftr::VectorT<T>::transformBy44ColMajorMat( const T m[16] ) const
{
   //Column Major (How OpenGL Stores the matrix)
   //| 0   4   8  12|
   //| 1   5   9  13|
   //| 2   6  10  14|
   //| 3   7  11  15|

   //Column Major indexing into the display dispMatrix (OpenGL stores dispMatrix this way)
   T x = this->x * m[0] + this->y * m[4] + this->z * m[8];
   T y = this->x * m[1] + this->y * m[5] + this->z * m[9];
   T z = this->x * m[2] + this->y * m[6] + this->z * m[10];

   VectorT<T> resultant( x, y, z );
   return resultant;
}

template< typename T >
VectorT<T> Aftr::VectorT<T>::transformBy33ColMajorMat( const T m[16] ) const
{
   //Column Major (How OpenGL Stores the matrix)
   //| 0   3  6 |
   //| 1   4  7 |
   //| 2   5  8 |

   //Column Major indexing into the display dispMatrix (OpenGL stores dispMatrix this way)
   T x = this->x * m[0] + this->y * m[3] + this->z * m[6];
   T y = this->x * m[1] + this->y * m[4] + this->z * m[7];
   T z = this->x * m[2] + this->y * m[5] + this->z * m[8];

   VectorT<T> resultant( x, y, z );
   return resultant;
}

template< typename T >
std::string VectorT<T>::toString() const
{
   return this->toString( 3 );
}

template< typename T >
VectorT<T>& VectorT<T>::fromString( const std::string& str )
{
   VectorT<T> v( str );
   (*this) = v;
   return *this;
}

template< typename T >
std::string VectorT<T>::toString(int length) const
{
   std::stringstream ss;
   ss.precision( length );
   ss << "(" << std::fixed << this->x << ", " << this->y << ", " << this->z << ")";
   return ss.str();
}

template< typename T >
std::string VectorT<T>::toStringBase64() const
{
   size_t numBytes = sizeof( T ) * 3;
   std::vector<unsigned char> dat( numBytes ); //Create vector with size of 3 * T, in bytes

   const unsigned char* c = reinterpret_cast<const unsigned char*>( &this->x );
   for( size_t i = 0; i < numBytes; ++i )
   {
      dat[i] = *c;
      ++c;
   }

   return VectorImpl::encodeBinaryToBase64( dat );
}

template< typename T >
VectorT<T> VectorT<T>::fromStringBase64( const std::string& s )
{
   std::vector<unsigned char> dat = VectorImpl::encodeBase64ToBinary( s );

   VectorT<T> t;

   if( dat.size() != sizeof( decltype( t )::value_type ) * 3 )
   {
      std::cout << "ERROR: " << AFTR_FILE_LINE_STR << ". Attempted to create either:\n"
         << "   1) VectorT<float> from a non 4 byte * 3 Base64 String\n"
         << "   2) VectorT<double> from a non 8 byte * 3 Base64 String\n"
         << "   Ensure one calls either:\n"
         << "   1) VectorD v = VectorD::fromStringBase64( a24ByteBase64Num );\n"
         << "   2) Vector  v = Vector::fromStringBase64( a12ByteBase64Num );\n"
         << "   Fix this problem. In the mean time I will crash here and let\n"
         << "   you read this very information message...";
      std::abort();
   }

   unsigned char* c = reinterpret_cast<unsigned char*>( &t.x );
   for( size_t i = 0; i < dat.size(); ++i )
   {
      *c = dat[i];
      ++c;
   }
   
   return t;
}

template< typename T >
T VectorT<T>::getTheta() const
{
   if( (fabs(x) - ZERO_THRESHOLD() ) > 0 )
   {
      if( fabs(y) - ZERO_THRESHOLD() > 0 )
      {
         if( x > 0 ) //if x is pos
         {
            if( y > 0 )
            {
               return( atan( y / x ) ); // x is pos and y is pos
            }
            else
               return( Aftr::PI*3/2 + (Aftr::TWOPI - ( (Aftr::PI*3/2) - atan( y / x ) ) ) ); // x is pos and y is neg
         }
         else //if x is neg
         { 
            if( y > 0 )
               return( Aftr::PI + atan( y / x ) ); //x is neg and y is pos
            else
               return( Aftr::PI + atan( y / x ) ); //x is neg and y is neg
         }
      }
      else //if y is ZERO
      {
         if( x > 0 )
            return 0; //x is pos and y is zero
         else
            return Aftr::PI; //x is neg and y is zero
      }
   }
   else
   {  //x is close to zero, so the y component must be checked
      if( fabs(y) - ZERO_THRESHOLD() > 0 )
      {
         if( y > 0 )
            return( Aftr::PI/2 ); //x is zero and y is pos
         else
            return( 3 * Aftr::PI/2 );  //x is zero and y is neg
      }
      else
      {
         return 0; //x is zero and y is zero
      }
   }
}

template< typename T >
T VectorT<T>::getPhi() const
{
   VectorT<T> xyPlane;
   xyPlane.x = this->x;
   xyPlane.y = this->y;
   xyPlane.z = 0;
   T theZ = this->z;
   T xyDist = xyPlane.magnitude();

   if( ( fabs( xyDist ) - ZERO_THRESHOLD() ) < 0 ) //X and Y components are zero
      return 0;

   T thePhi = fabs( atanf( theZ / xyDist ) );

   if( theZ > 0 )
      return -1.0f * thePhi;
   else
      return thePhi;

   //first need to rotate so vector lies in xz plane
   //then compute phi
   //VectorT<T> v( this );
   //v.rotate( 0, -this->getTheta() ); //v now lies in XZ plane

   //if( (fabs(x) - ZERO_THRESHOLD) > 0 )
   //{
   //   if( (fabs(z) - ZERO_THRESHOLD) > 0 )
   //   {
   //      if( z > 0 )
   //         return( -atan( z / x ) ); //x is pos or neg and z is pos
   //      else
   //         return( -atan( z / x ) ); //x is pos or neg and z is neg
   //   }
   //   else
   //   {
   //      //x is pos or neg and z is zero
   //      return 0;
   //   }
   //}
   //else
   //{  //x is zero
   //   if( (fabs(z) - ZERO_THRESHOLD) > 0 )
   //   {
   //      if( z > 0 )
   //         return( -Aftr::PI/2 ); //x is zero and z is positive
   //      else
   //         return( Aftr::PI/2 ); //x is zero and z is negative
   //   }
   //   else //z is zero
   //   {
   //      return 0; //x is zero and z is zero
   //   }
   //}
}

//derived from http://en.wikipedia.org/wiki/Geodetic_system
template< typename T >
VectorT<T> VectorT<T>::toECEFfromWGS84() const
{
   //T latitude, longitude, a, e2, chi, f, h;
   //VectorT<T> temp;

   //latitude = this->x * DEGtoRAD;
   //longitude = this->y * DEGtoRAD;
   //h = this->z;

   //a = 6378137.0f;
   //f = 1/298.257223563f;
   //e2 = 2*f -(f * f);

   //chi = sqrt(1-e2*(sin(latitude))*sin(latitude)); 
   //temp.x = (a/chi +h)*cos(latitude)*cos(longitude); 
   //temp.y = (a/chi +h)*cos(latitude)*sin(longitude); 
   //temp.z = (a*(1-e2)/chi + h)*sin(latitude);

   //return temp;

   //This code is rewritten to match the LlhToEcef(Llh) in
   //Dr. Raquet's matlab utility. The previous code computes 
   //that the north pole {90,0,0} is at an ecef coord of
   //  lla north pole is( 90.0000000000, 0.0000000000, 0.0000000000 )
   //  ecef north pole is( 0.0778700279, 0.0000000000, 6356752.3144750167 )
   //Where as Dr. Raquet's code says:
   //LlhToEcef([90,0,0]*dtr)
   //ans = 3.91862092481445e-10, 0, 6356752.31424522
   //I believe this leads to an altitude error of up to 8 cm between two
   //LLAs that < 30m of each other. (That is LLA -> ECEF -> nav frame
   //causes an altitude discrepancy.

   //% initial conditions
   T a = 6378137.0;
   T e2 = 0.00669437999013;

   double latRad = this->x * Aftr::DEGtoRADd;
   double lonRad = this->y * Aftr::DEGtoRADd;
   
   T sinLatRad = std::sin( latRad );
   T e2sinLatSq = e2*( sinLatRad*sinLatRad );

   T rn = a / std::sqrt( 1 - e2sinLatSq );
   T R = ( rn + this->z ) * std::cos( latRad );

   VectorT<T> ecefVec;
   ecefVec.x = R * std::cos( lonRad );
   ecefVec.y = R * std::sin( lonRad );
   ecefVec.z = ( rn * ( 1 - e2 ) + this->z ) * std::sin( latRad );

   return ecefVec;
}

template< typename T >
VectorT<T> VectorT<T>::toECEFfromGRS80() const
{
   T latitude, longitude, a, e2, chi, f, h;
   VectorT<T> temp;

   latitude = this->x * DEGtoRAD;
   longitude = this->y * DEGtoRAD;
   h = this->z;

   a = GRS80::getMajorSemiaxisInMeters();
   f = GRS80::getRecipricalOfFlattening();
   e2 = GRS80::getEccentricitySquarred();

   chi = sqrt(1-e2*(sin(latitude))*sin(latitude)); 
   temp.x = (a/chi +h)*cos(latitude)*cos(longitude); 
   temp.y = (a/chi +h)*cos(latitude)*sin(longitude); 
   temp.z = (a*(1-e2)/chi + h)*sin(latitude);

   return temp;
}

//derived from http://en.wikipedia.org/wiki/Geodetic_system
template< typename T >
VectorT<T> VectorT<T>::toWGS84fromECEF() const
{
   T a, f, b, e2, ep2, r2, r, E2, F, G, c, s, P, Q, ro, tmp, U, V, zo, h, phi, lambda;
   T Z = this->z;
   T X = this->x;
   T Y = this->y;
   //phi - latitude
   //lamba - longitude
   //h - elevation

   a = 6378137.0; // earth semimajor axis in meters
   f = 1/298.257223563f; //reciprocal flattening
   b = a*(1-f);// semi-minor axis

   e2 = 2*f-f*f;// first eccentricity squared
   ep2 = f*(2-f)/(pow((1-f),2.0f)); // second eccentricity squared

   r2 = X * X + Y * Y;
   r = sqrt(r2);
   E2 = a*a - b*b;
   F = 54*b*b*Z*Z;
   G = r2 + (1-e2)*Z*Z - e2*E2;
   c = (e2*e2*F*r2)/ (G*G*G);
   s = pow( 1 + c + sqrt(c*c + 2*c) ,(1/3));
   P = F/(3*pow(s+1/s+1,2.0f)*G*G);
   Q = sqrt(1+2*e2*e2*P);
   ro = -(e2*P*r)/(1+Q) + sqrt((a*a/2)*(1+1/Q) - ((1-e2)*P*Z*Z)/(Q*(1+Q)) - P*r2/2);
   tmp = pow(r - e2*ro,2.0f);
   U = sqrt( tmp + Z*Z );
   V = sqrt( tmp + (1-e2)*Z*Z );
   zo = (b*b*Z)/(a*V);

   h = U*( 1 - (b*b)/(a*V));
   phi = atan( (Z + ep2*zo)/r );
   lambda = atan2(Y,X);

   phi *= Aftr::RADtoDEGd;
   lambda *= Aftr::RADtoDEGd;

   return VectorT<T>(phi,lambda,h);
}

template< typename T >
VectorD VectorT<T>::toVecD() const
{
   return VectorD( static_cast<double>( x ), static_cast<double>( y ), static_cast<double>( z ) );
}

template< typename T >
Vector VectorT<T>::toVecS() const
{
   return Vector( static_cast<float>( x ), static_cast<float>( y ), static_cast<float>( z ) );
}

//NOAA Manual NOS NGS 5, State Plane Coordinate System of 1983 - James E Stern
template< typename T >
VectorT<T> VectorT<T>::toCartesianFromLambertConformalConicUsingGRS80Ellipsoid(T referenceLat, T referenceLon, T parallel1, T parallel2)
{
   VectorT<T> temp;

   double x = this->x * Aftr::DEGtoRADd;
   double y = this->y * Aftr::DEGtoRADd;
   referenceLat *= Aftr::DEGtoRADd;
   referenceLon *= Aftr::DEGtoRADd;
   parallel1 *= Aftr::DEGtoRADd;
   parallel2 *= Aftr::DEGtoRADd;
   long double parallelc = (parallel1 + parallel2) / 2;

   long double lat = referenceLat;
   long double lon = referenceLon;

   long double f = GRS80::getFlattening();
   long double e = sqrt(2 * f - f * f);
   long double e2 = 2 * f - f*f;

   auto Q = [e](long double phi) { return .5 * (log((1 + sin(phi)) / (1 - sin(phi))) - e * log((1 + e*sin(phi)) / (1 - e*sin(phi)))); };
   auto W = [e2](long double phi) { return sqrt(1 - e2 * sin(phi) * sin(phi)); };

   long double a = GRS80::getMajorSemiaxisInMeters();

   long double Qs = Q(parallel1);
   long double Qn = Q(parallel2);
   long double Ws = W(parallel1);
   long double Wn = W(parallel2);
   long double sinphi0 = log(Wn * cos(parallel1) / (Ws * cos(parallel2))) / (Qn - Qs);
   parallelc = asin(sinphi0);
   long double Qb = Q(lat);

   long double K = a * cos(parallel1) * exp(Qs * sinphi0) / (Ws * sinphi0);
   K = a * cos(parallel2) * exp(Qn * sinphi0) / (Wn * sinphi0);
   long double Qx = Q(x);

   auto R = [sinphi0, K](long double q) { return K / exp(q * sinphi0);  };

   long double Rx = R(Qx);
   long double Rb = R(Qb);
   long double k = sqrt((1 - e2 * sin(x) * sin(x))) * (Rx * sinphi0) / (a * cos(x));
   long double gamma = (y - lon) * sinphi0;
   //Nb and E applied outside function
   temp.y = Rb - Rx * cos(gamma);
   temp.x = Rx * sin(gamma);
   temp.y *= k;

   return temp;
}
template< typename T >
VectorT<T> VectorT<T>::toGRS80FromLambertConformalConic( T referenceLat, T referenceLon, T parallel1, T parallel2 )
{
   VectorT<T> temp;

   referenceLat *= Aftr::DEGtoRADd;
   referenceLon *= Aftr::DEGtoRADd;
   parallel1 *= Aftr::DEGtoRADd;
   parallel2 *= Aftr::DEGtoRADd;

   long double f = GRS80::getFlattening();
   long double e = sqrt(2*f - f * f);

   long double m1 = cos( parallel1 ) / ( sqrt( 1 - e * e * sin( parallel1 ) * sin( parallel1 ) ) );
   long double m2 = cos( parallel2 ) / ( sqrt( 1 - e * e * sin( parallel2 ) * sin( parallel2 ) ) );
   // double t = tan( Aftr::PI / 4 - x / 2) / ( pow( (1 - e * sin( x ) ) / ( 1 + e * sin( x ) ), e / 2) );
   long double t0 = tan( Aftr::PId / 4 - referenceLat / 2) / ( pow( (1 - e * sin( referenceLat ) ) / ( 1 + e * sin( referenceLat ) ), e / 2) );
   long double t1 = tan( Aftr::PId / 4 - parallel1 / 2) / ( pow( (1 - e * sin( parallel1 ) ) / ( 1 + e * sin( parallel1 ) ), e / 2) );
   long double t2 = tan( Aftr::PId / 4 - parallel2 / 2) / ( pow( (1 - e * sin( parallel2 ) ) / ( 1 + e * sin( parallel2 ) ), e / 2) );

      
   long double n = (log( m1 ) - log( m2 )) / (log(t1) - log(t2) );
   long double F = m1 / ( n * pow(t1, n));


   long double rho0 = F * pow( t0, n ) * GRS80::getMajorSemiaxisInMeters();

   long double rho = sqrt(this->x * this->x + (rho0 - this->y) * (rho0 - this->y));
   rho *= rho * n < 0 ? -1 : 1;

   long double tt = pow( rho / ( F * GRS80::getMajorSemiaxisInMeters() ), 1 / n );

   long double gamma = atan2( (long double) this->x, (rho0 - (long double) this->y) );

   long double phi = Aftr::PI / 2 - 2 * atan( tt );
   long double phi2 = 0;

   do
   {
      // std::cout << "Phi: " << phi << std::endl;
      phi2 = phi;
      phi = Aftr::PI / 2 - 2 * atan( tt * pow( (1 - e * sin( phi2 ) ) / (1 + e * sin( phi2 ) ), e / 2 ) );
   }
   while( std::abs<double>(phi - phi2) > .00001 );

   long double lamda = gamma / n + referenceLon;
      
  

   temp.y = lamda * Aftr::RADtoDEGd;
   temp.x = phi  * Aftr::RADtoDEGd;
   //     std::cin.get();
   return temp;   
}

// template <typename T>
// VectorT<T> VectorT<T>::toGRS80FromTransverseMercator(T originLat, T originLon, T falseNorthing, T falseEasting)
// {
//       T phi0 = originLat * Aftr::DEGtoRADd;
//       //T S0 = 3430631.2260; // phi0 * k0;
//       T r = 6367449.14577;
//       T cphi0 = cos(phi0);
//       T cphi02 = cphi0 * cphi0;
//       T cphi04 = cphi02 * cphi02;
//       T cphi06 = cphi04 * cphi02;
//       //these should probably be moved into the GRS80 class?
//       T U0 = -.005048250776;
//       T U2 = .000021259204;
//       T U4 = -.000000111423;
//       T U6 = 0.000000000626;
//       T omegao = phi0 + sin(phi0) * cphi0 * (U0 + U2 * cphi02 + U4 * cphi04 + U6 * cphi06);
//       T S0 = k0 * omegao * r;
//       T a = GRS80::getMajorSemiaxisInMeters();
//       T b = GRS80::getMinorSemiaxisInMeters();
//       T e2 = GRS80::getEccentricitySquarred();
//       T eprime2 = e2 / (1 - e2);
//       T lamda0 = originLon * Aftr::DEGtoRADd;
//       T Eprime = E - E0;

//       T omega = (N - N0 + S0) / (k0 * r); //line
//       T comega = cos(omega);
//       T comega2 = comega * comega;
//       T comega4 = comega2 * comega2;
//       T comega6 = comega4 * comega2;
//       T V0 = .005022893948;
//       T V2 = .000029370625;
//       T V4 = .000000235059;
//       T V6 = .000000002182;
//       T phif = omega + (sin(omega) * comega) * (V0 + V2 * comega2 + V4 * comega4 + V6 * comega6); //line
//       T Rf = k0 * a / sqrt((1 - e2 * sin(phif) * sin(phif)));                                     //line
//       T Q = Eprime / Rf;                                                                          //line
//       T tf = tan(phif);
//       T nf = eprime2 * cos(phif) * cos(phif);
//       T tf2 = tf * tf;
//       T tf4 = tf2 * tf2;
//       T tf6 = tf4 * tf2;
//       T nf2 = nf * nf;
//       T nf4 = nf2 * nf2;
//       T B2 = -.5 * tf * (1 + nf2);                                                       //line
//       T B4 = -1.0 / 12 * (5 + 3 * tf2 + nf2 * (1 - 9 * tf2) - 4 * nf4);                  //line
//       T B6 = 1.0 / 360 * (61 + 90 * tf2 + 45 * tf4 + nf2 * (46 - 252 * tf2 - 90 * tf4)); //line
//       T Q2 = Q * Q;
//       T phi = phif + B2 * Q2 * (1 + Q2 * (B4 + B6 * Q2));                 //line
//       T B3 = -1.0 / 6 * (1 + 2 * tf2 + nf2);                              //line
//       T B5 = 1.0 / 120 * (5 + 25 * tf2 + 24 * tf4 + nf2 * (6 + 8 * tf2)); //line
//       T B7 = -1.0 / 5040 * (61 + 662 * tf2 + 1320 * tf4 + 720 * tf6);     //line
//       T L = Q * (1 + Q2 * (B3 + Q2 * (B5 + B7 * Q2)));                    //line
//       T lamda = lamda0 - L / cos(phif);                                   //line
//       T D1 = tf;                                                          //line
//       T D3 = -1.0 / 3 * (1 + tf2 - nf2 - 2 * nf4);                        //line
//       T D5 = 1.0 / 15 * (2 + 5 * tf2 + 3 * tf4);                          //line
//       T gamma = D1 * Q * (1 + Q2 * (D3 + D5 * Q2));                       //line
//       T G2 = .5 * (1 + nf2);                                              //line
//       T G4 = 1.0 / 12 * (1 + 5 * nf2);                                    //line
//       T k = k0 * (1 + G2 * Q2 * (1 + G4 * Q2));

//       return Vector(phi * Aftr::RADtoDEGd, lamda * RADtoDEGd, 0);
// }

template< typename T >
VectorT<T> VectorT<T>::toTransverseMercatorFromGRS80(T originLat, T originLon, T k0)
{
   
   T phi = x * Aftr::DEGtoRADd;
   T phio = originLat * Aftr::DEGtoRADd;
   T lamda = y * Aftr::DEGtoRADd;
   T lamdao = originLon * Aftr::DEGtoRADd;
   T L = (lamdao - lamda) * cos(phi);
   T cosphi2 = cos(phi) * cos(phi);
   T cosphio2 = cos(phio) * cos(phio);
   T U0 = -.005048250776;
   T U2 = .000021259204;
   T U4 = .000000111423;
   T U6 = .000000000626;
   T r = 6367449.14577;
   T omega = phi + (sin(phi) * cos(phi)) * (U0 + cosphi2 * (U2 + cosphi2 * (U4 + U6 * cosphi2)));
   T omegao = phio + (sin(phio) * cos(phio)) * (U0 + cosphio2 * (U2 + cosphio2 * (U4 + U6 * cosphio2)));
   T S0 = k0 * omegao * r;
   T a = GRS80::getMajorSemiaxisInMeters();
   T b = GRS80::getMinorSemiaxisInMeters();
   T e2 = GRS80::getEccentricitySquarred();
   T eprime2 = e2 / (1 - e2);
   T eta2 = eprime2 * cos(phi) * cos(phi);

   T S = k0 * omega * r;

   T R = k0 * a / sqrt(1 - e2 * sin(phi) * sin(phi));
   T t = tan(phi);
   T t2 = t*t;
   T t4 = t2*t2;
   T t6 = t4 * t2;
   T A2 = .5 * R * t;
   T A4 = 1.0 / 12 * (5 - t2 + eta2 * (9 + 4 * eta2));
   T A6 = 1.0 / 360 * (61 - 58 * t2 + t4 + eta2 * (270 - 330 * t2));
   T ndiff = A2 * L * L * (1 + L * L * (A4 + A6 * L * L));
   T N = S - S0 + ndiff;
   T A1 = -1 * R;
   T A3 = 1.0 / 6 * (1 - t2 + eta2);
   T A5 = 1.0 / 120 * (5 - 18 * t2 + t4 + eta2 * (14 - 58 * t2));
   T A7 = 1.0 / 5040 * (61 - 479 * t2 + 179 * t4 - t6);
   T i7 = (A5 + L * L * A7);
   T i5 = (A3 + L * L * i7);
   T i3 = (1 + L * L * i5);
   T diff2 = A1 * L * i3;
   T E = diff2;

   VectorT<T> temp;
   temp.x = E;
   temp.y = N;
   temp.z = this->z;
   return temp;

}


}