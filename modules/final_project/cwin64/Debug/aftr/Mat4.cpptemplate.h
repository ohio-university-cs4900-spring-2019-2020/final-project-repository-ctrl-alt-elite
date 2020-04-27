//using namespace Aftr;

//template bool Mat4::is_T_Equal<float>( float x, float y, float epsilon );
//template bool Mat4::is_T_Equal<double>( double x, double y, double epsilon );
template< typename T >
bool Aftr::Mat4T<T>::is_T_Equal( T x, T y, T epsilon )
{
   if( std::abs( x - y ) <= epsilon )
      return true;
   return false;
}

template< typename T >
void Aftr::Mat4T<T>::setToIdentity4x4( T* m )
{
   m[0]  = 1; m[4]  = 0; m[8]  = 0; m[12] = 0;
   m[1]  = 0; m[5]  = 1; m[9]  = 0; m[13] = 0;
   m[2]  = 0; m[6]  = 0; m[10] = 1; m[14] = 0;
   m[3]  = 0; m[7]  = 0; m[11] = 0; m[15] = 1;
}

template< typename T >
Aftr::Mat4T<T>::Mat4T()
{   
   Aftr::Mat4T<T>::setToIdentity4x4( this->m.data() );

   static_assert( sizeof( Mat4T<T> ) == sizeof( T ) * 16,
                  "Aftr Compiler Halt: Mat4T<T> MUST not change its size of 16*T.\n" \
                  "This would cause float* mat to have a different layout than std::vector<Mat4<float>>.\n" \
                  "This would ultimately hurt performance." );
}


template< typename T >
Aftr::Mat4T<T>::Mat4T( const Mat4T<T>& m )
{
   *this = m;
}

template< typename T >
Aftr::Mat4T<T>::Mat4T( const T* mat4ToBeCopied )
{
   if( mat4ToBeCopied != nullptr )
      memcpy( this->m.data(), mat4ToBeCopied, 16 * sizeof( T ) );
   else
      Aftr::Mat4T<T>::setToIdentity4x4( this->m.data() );
}

template< typename T >
Aftr::Mat4T<T>::Mat4T( const VectorT<T>& x, const VectorT<T>& y, const VectorT<T>& z )
{
   this->m[0] = x.x; this->m[4] = y.x; this->m[8]  = z.x; this->m[12] = 0;
   this->m[1] = x.y; this->m[5] = y.y; this->m[9]  = z.y; this->m[13] = 0;
   this->m[2] = x.z; this->m[6] = y.z; this->m[10] = z.z; this->m[14] = 0;
   this->m[3] = 0;   this->m[7] = 0;   this->m[11] = 0;   this->m[15] = 1;
}

template< typename T >
Aftr::Mat4T<T>::Mat4T( std::array<T, 16> const& mat )
{
   std::copy( std::begin( mat ), std::end( mat ), std::begin( this->m ) );
}

template< typename T >
Aftr::Mat4T<T>::Mat4T( const std::string& str, bool inputStringIsColumnMajor )
{
   //This regex matches a floating point number (RegEx explained at http://www.regular-expressions.info/Tingpoint.html)
   std::string regEx = "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?";
   std::vector< std::string > vals( 16, "0" );
   #ifdef AFTR_CONFIG_USE_BOOST
   {
      boost::sregex_iterator i( str.begin(), str.end(), boost::regex( regEx ) );
      boost::sregex_iterator end;

      size_t count = 0;
      while( i != end && count <= 16 )
      {
         vals[count] = i->str();
         ++i; ++count;
      }
   }
   #else
      std::cout << "WARNING: AFTR_CONFIG_USE_BOOST is not defined - no regEx to parse Mat4T( const std::string& ) - will return Identity..." << AFTR_FILE_LINE_STR << std::endl;
   #endif

   if( vals.size() >= 16 )
   {
      std::stringstream ss;
      if( !inputStringIsColumnMajor )
      {
         ss << vals[0]  << " " << vals[1]  << " " << vals[2]  << " "  << vals[3] << " "
            << vals[4]  << " " << vals[5]  << " " << vals[6]  << " "  << vals[7] << " "
            << vals[8]  << " " << vals[9]  << " " << vals[10] << " " << vals[11] << " "
            << vals[12] << " " << vals[13] << " " << vals[14] << " " << vals[15];
      }
      else //input stream is column major, we can only read in a row-major fashion, therefore we need to transpose the input before placing it in our array
      {
         ss << vals[0] << " " << vals[4] << " " << vals[8]  << " " << vals[12] << " "
            << vals[1] << " " << vals[5] << " " << vals[9]  << " " << vals[13] << " "
            << vals[2] << " " << vals[6] << " " << vals[10] << " " << vals[14] << " "
            << vals[3] << " " << vals[7] << " " << vals[11] << " " << vals[15];
      }

      for( size_t i = 0; i < 16; ++i )
         ss >> this->m[i];
   }
   else
   {
      std::cout << "WARNING!!! Aftr::Mat4T<T>::Mat4T<T>( const std::string& str ), could not match 3 Ting point values, setting Mat4T<T> to zero...\n";
   }
}

template< typename T >
void Aftr::Mat4T<T>::set( const T* mat4x4 )
{
   std::memcpy( this->m.data(), mat4x4, 16 * sizeof( T ) );
}

template< typename T >
void Aftr::Mat4T<T>::setMeToIdentity()
{
   Mat4T::setToIdentity4x4( this->m.data() );
}

template< typename T >
Aftr::VectorT<T> Aftr::Mat4T<T>::operator *( const Aftr::VectorT<T>& v ) const
{
   Aftr::VectorT<T> w = { 0, 0, 0 };

   w.x = m[0] * v.x + m[4] * v.y + m[8]  * v.z;
   w.y = m[1] * v.x + m[5] * v.y + m[9]  * v.z;
   w.z = m[2] * v.x + m[6] * v.y + m[10] * v.z;

   return w;
}

template< typename T >
std::pair< Aftr::VectorT<T>, T > Aftr::Mat4T<T>::operator *( const std::pair< const Aftr::VectorT<T>&, T >& homogeniusCoord ) const
{
   //return std::make_pair( 1, 1.3f );

   const VectorT<T>& v = homogeniusCoord.first;
   T h = homogeniusCoord.second;
   Aftr::VectorT<T> w = { 0, 0, 0 };
   T s = 0;

   w.x = m[0] * v.x + m[4] * v.y + m[8]  * v.z + m[12] * h;
   w.y = m[1] * v.x + m[5] * v.y + m[9]  * v.z + m[13] * h;
   w.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * h;
     s = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * h;

   return std::make_pair( w, s );
   //return std::make_pair( w, h );
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::operator *( const Aftr::Mat4T<T>& m ) const
{
   Aftr::Mat4T<T> result;
   T* p = result.m.data();
   const T* b = this->m.data();
   const T* a = m.m.data();
   
   //we want to post multiply a by b. So we swap the order the matrices are multiplied above (ie, b is "this" and a is "m")
   for( size_t r = 0; r < 4; ++r )
      for( size_t c = 0; c < 4; ++c )
         p[r * 4 + c] = a[r * 4 + 0] * b[0 * 4 + c] +
                        a[r * 4 + 1] * b[1 * 4 + c] +
                        a[r * 4 + 2] * b[2 * 4 + c] +
                        a[r * 4 + 3] * b[3 * 4 + c];
   return result;
}

template< typename T >
Aftr::Mat4T<T>& Aftr::Mat4T<T>::operator *=( const Aftr::Mat4T<T>& m)
{
   *this = m  * ( *this );
   return *this;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::operator +(const Aftr::Mat4T<T>& m) const
{
   Aftr::Mat4T<T> result;
   T* p = result.m.data();
   const T* b = this->m.data();
   const T* a = m.m.data();

   //loop and add each element
   for (size_t i = 0; i < 16; i++)
      p[i] = a[i] + b[i];
			
   return result;
}

template< typename T >
Aftr::Mat4T<T>& Aftr::Mat4T<T>::operator =( const Aftr::Mat4T<T>& m )
{
   if( this != &m )
   {
      for( size_t i = 0; i < 16; ++i )
         this->m[i] = m.m[i];
      //std::copy( std::begin( m.m ), std::end( m.m ), std::begin( this->m ) ); // as of 2015, this is much slower than a for loop
   }
   return *this;
}

template< typename T >
bool Aftr::Mat4T<T>::operator ==( const Aftr::Mat4T<T>& m ) const
{
   for( size_t i = 0; i < this->m.size(); ++i )
   {
      if( std::abs( this->m[i] - m.m[i] ) > ZERO_THRESHOLD() )
         return false;
   }
   return true;
}

template< typename T >
bool Aftr::Mat4T<T>::operator !=( const Aftr::Mat4T<T>& m ) const
{
   if( (*this) == m )
      return false;
   return true;
}

template< typename T >
T& Aftr::Mat4T<T>::operator [] ( size_t i )
{
   return this->m[i];
}

template< typename T >
T Aftr::Mat4T<T>::operator [] ( size_t i ) const
{
   return this->m[i];
}

template< typename T >
T& Aftr::Mat4T<T>::at( size_t i )
{
   if( i > 15 )
   {
      //ERROR, replace with exception at some point
      std::cout << "ERROR: " << AFTR_FILE_LINE_STR << " User attempted to access a component outside the interval [0,15].  Exiting. " << std::endl;
      std::cin.get();
      exit( -1 );
   }
   return this->m[i];
}

template< typename T >
T Aftr::Mat4T<T>::at( size_t i ) const
{
   if( i > 15 )
   {
      //ERROR, replace with exception at some point
      std::cout << "ERROR: " << AFTR_FILE_LINE_STR << " User attempted to access a component outside the interval [0,15].  Exiting. " << std::endl;
      std::cin.get();
      exit( -1 );
   }
   return this->m[i];
}

template< typename T >
bool Aftr::Mat4T<T>::isEqual( const Aftr::Mat4T<T>& m, T tolerance ) const
{
   for( size_t i = 0; i < this->m.size(); ++i )
   {
      if( std::abs( this->m[i] - m[i] ) > tolerance )
         return false;
   }
   return true;
}

template< typename T >
bool Aftr::Mat4T<T>::isValidForEachComponent() const
{
   for( size_t i = 0; i < 16; ++i )
      if( std::isinf( this->m[i] ) || std::isnan( this->m[i] ) )
         return false;

   return true;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::rotate( const Aftr::VectorT<T>& axisNormalized, T angleRads ) const
{
   return Aftr::Mat4T<T>::rotateIdentityMat( axisNormalized, angleRads ) * ( *this ); // transform current matrix by rotated identity
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::rotateIdentityMat( const Aftr::VectorT<T>& axisNormalized, T angleRads )
{
   if( ! Aftr::Mat4T<T>::is_T_Equal( axisNormalized.magnitudeSquared(), static_cast<T>(1.0), static_cast<T>(0.0001) ) )
   {
      std::cout << "ERROR:" << AFTR_FILE_LINE_STR << ": Expected rotation axis must be unit length, but was passed "
         << axisNormalized.toString( 5 ) << " (magnitude " << axisNormalized.magnitude() << ")...\n"
         << "Ensure rotation axis is unit length.";
      std::abort();
   }

   Aftr::Mat4T<T> r;
   T* m = r.m.data();
   T u = axisNormalized.x;
   T v = axisNormalized.y;
   T w = axisNormalized.z;
   T t = angleRads;

   T cost = std::cos( t );
   T sint = std::sin( t );

   m[0] = u*u + ( 1.0f - u*u ) * cost;    m[4] = u*v*( 1.0f - cost ) - w * sint; m[8] = u*w*( 1.0f - cost ) + v * sint; m[12] = 0.0f;
   m[1] = u*v*( 1.0f - cost ) + w * sint; m[5] = v*v + ( 1.0f - v*v ) * cost;    m[9] = v*w*( 1.0f - cost ) - u * sint; m[13] = 0.0f;
   m[2] = u*w*( 1.0f - cost ) - v * sint; m[6] = v*w*( 1.0f - cost ) + u*sint;   m[10] = w*w + ( 1.0f - w*w )* cost;    m[14] = 0.0f;
   m[3] = 0.0f;                           m[7] = 0.0f;                           m[11] = 0.0f;                          m[15] = 1.0f;

   return r; //Since this static method only rotates the identity matrix, we do not need to accumulate r with the current matrix
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::translate( const Aftr::VectorT<T>& t ) const
{
   Aftr::Mat4T<T> trM( *this );
   VectorT<T> tr = ( *this ) * t; //transform t through upper 3x3 matrix
   trM.setPosition( trM.getPosition() + tr ); //add new translate amount to the existing translate amount
   return trM;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::translateIdentityMat( const Aftr::VectorT<T>& t )
{
   Aftr::Mat4T<T> tr;
   tr[12] = t.x;
   tr[13] = t.y;
   tr[14] = t.z;
   return tr;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::scale( const Aftr::VectorT<T>& s ) const
{
   Aftr::Mat4T<T> sc( *this );
   sc.setX( sc.getX() * s.x );
   sc.setY( sc.getY() * s.y );
   sc.setZ( sc.getZ() * s.z );
   return sc;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::scaleIdentityMat( const Aftr::VectorT<T>& s )
{
   Aftr::Mat4T<T> sc;
   sc[0] = s.x;
   sc[5] = s.y;
   sc[10] = s.z;
   return sc;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::transposeUpperLeft3x3() const
{
   Aftr::Mat4T<T> transpose(*this);
   T* t = transpose.m.data();
   const T* s = this->m.data();
   
   t[0] = s[0]; t[4] = s[1]; t[8]  = s[2];
   t[1] = s[4]; t[5] = s[5]; t[9]  = s[6];
   t[2] = s[8]; t[6] = s[9]; t[10] = s[10];

   return transpose;
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::transpose4x4() const
{
   Aftr::Mat4T<T> t;
   for( size_t r = 0; r < 4; ++r )
      for( size_t c = 0; c < 4; ++c )
         t[ r * 4 + c ] = ( *this )[r + c * 4 ];

   return t;
}

template< typename T >
std::string Aftr::Mat4T<T>::toString() const
{
   return this->toString( 3 );
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::fromString( const std::string& str, bool inputStringIsColumnMajor )
{
   Aftr::Mat4T<T> m( str, inputStringIsColumnMajor );   
   return m;
}

template< typename T >
std::string Aftr::Mat4T<T>::toString( size_t length ) const
{
   //print each column using the minimal number of spaces to keep the decimals aligned, with at one space between each column
   std::stringstream ss;
   ss.precision( length );
   ss << std::fixed << std::showpoint;

   std::string colWidth = ""; 
   std::streamsize w[4] = { 0, 0, 0, 0 };

   for( size_t i = 0; i < 4; ++i ) //columns
   {
      for( size_t j = 0; j < 4; ++j ) //rows
      {
         ss << this->m[i * 4 + j]; //read one column per each iteration of inner loop
         ss >> colWidth;
         if( (colWidth.length() + 1) > static_cast<size_t>( w[i] ) )
            w[i] = colWidth.length() + 1;
         ss.str( "" ); ss.clear(); // reset stringstream so we can reuse it to output the matrix now that we know the maximal number of spaces we need to print it out
         //std::cout << "Column " << i << " width is " << w[i] << ", txt was " << colWidth << "...\n";
      }      
   }

   ss << std::setw( w[0] - 1 ) << this->m[0] << std::setw( w[1] ) << this->m[4] << std::setw( w[2] ) << this->m[8] << std::setw( w[3] ) << this->m[12] << "\n"
      << std::setw( w[0] - 1 ) << this->m[1] << std::setw( w[1] ) << this->m[5] << std::setw( w[2] ) << this->m[9] << std::setw( w[3] ) << this->m[13] << "\n"
      << std::setw( w[0] - 1 ) << this->m[2] << std::setw( w[1] ) << this->m[6] << std::setw( w[2] ) << this->m[10] << std::setw( w[3] ) << this->m[14] << "\n"
      << std::setw( w[0] - 1 ) << this->m[3] << std::setw( w[1] ) << this->m[7] << std::setw( w[2] ) << this->m[11] << std::setw( w[3] ) << this->m[15] << "\n";
   return ss.str();
}

template< typename T >
std::string Aftr::Mat4T<T>::toStringWithVecMagnitudes( size_t length ) const
{
   std::stringstream ss;
   ss << this->toString( length );
   ss << "xDir Mag " << this->getX().magnitude() << "\n";
   ss << "yDir Mag " << this->getY().magnitude() << "\n";
   ss << "zDir Mag " << this->getZ().magnitude() << "\n";
   return ss.str();
}

template< typename T >
Aftr::Mat4T<double> Aftr::Mat4T<T>::toMatD() const
{
   Aftr::Mat4T<double> dm;
   for( size_t i = 0; i < 16; ++i )
      dm.m[i] = static_cast<double>( this->m[i] );
   return dm;
}

template< typename T >
Aftr::Mat4T<float> Aftr::Mat4T<T>::toMatS() const
{
   Aftr::Mat4T<float> fm;
   for( size_t i = 0; i < 16; ++i )
      fm.m[i] = static_cast<float>( this->m[i] );
   return fm;
}

template< typename T >
Aftr::VectorT<T> Aftr::Mat4T<T>::getX() const
{
   Aftr::VectorT<T> x( this->m[0], this->m[1], this->m[2] );
   return x;
}

template< typename T >
Aftr::VectorT<T> Aftr::Mat4T<T>::getY() const
{
   Aftr::VectorT<T> y( this->m[4], this->m[5], this->m[6] );
   return y;
}

template< typename T >
Aftr::VectorT<T> Aftr::Mat4T<T>::getZ() const
{
   Aftr::VectorT<T> z( this->m[8], this->m[9], this->m[10] );
   return z;
}

template< typename T >
Aftr::VectorT<T> Aftr::Mat4T<T>::getPosition() const
{
   Aftr::VectorT<T> trans( this->m[12], this->m[13], this->m[14] );
   return trans;
}

template< typename T >
Aftr::VectorT<T> Aftr::Mat4T<T>::getVecCol( int i ) const
{
   if( i < 0 || i > 3 )
   {
      std::cout << "ERROR: " << AFTR_FILE_LINE_STR << ": cannot extract column " << i << ", out of bounds...\n";
      std::abort();
   }
   if( i == 0 )
      return this->getX();
   else if( i == 1 )
      return this->getY();
   else if( i == 2 )
      return this->getZ();
   else( i == 3 );
      return this->getPosition();
}

template< typename T >
Aftr::Mat4T<T> Aftr::Mat4T<T>::getUpperLeft3x3AsMat4() const
{
   Aftr::Mat4T<T> m( *this );
   T* t = m.m.data();   
                                  t[12] = 0;
                                  t[13] = 0;
                                  t[14] = 0;
   t[3] = 0; t[7] = 0; t[11] = 0; t[15] = 1;

   return m;
}

template< typename T >
void Aftr::Mat4T<T>::setX( const Aftr::VectorT<T>& xVec )
{
   this->m[0] = xVec.x;
   this->m[1] = xVec.y;
   this->m[2] = xVec.z;
}

template< typename T >
void Aftr::Mat4T<T>::setY( const Aftr::VectorT<T>& yVec )
{
   this->m[4] = yVec.x;
   this->m[5] = yVec.y;
   this->m[6] = yVec.z;
}

template< typename T >
void Aftr::Mat4T<T>::setZ( const Aftr::VectorT<T>& zVec )
{
   this->m[8]  = zVec.x;
   this->m[9]  = zVec.y;
   this->m[10] = zVec.z;
}

template< typename T >
void Aftr::Mat4T<T>::setPosition( const Aftr::VectorT<T>& trans )
{
   this->m[12] = trans.x;
   this->m[13] = trans.y;
   this->m[14] = trans.z;
}

template< typename T >
void Aftr::Mat4T<T>::setVecCol( int i, const VectorT<T>& vec )
{
   if( i < 0 || i > 3 )
   {
      std::cout << "ERROR: " << AFTR_FILE_LINE_STR << ": cannot insert column " << i << ", out of bounds...\n";
      std::abort();
   }
   if( i == 0 )
      return this->setX(vec);
   else if( i == 1 )
      return this->setY(vec);
   else if( i == 2 )
      return this->setZ(vec);
   else( i == 3 );
      return this->setPosition(vec);
}

template< typename T >
void Aftr::Mat4T<T>::setScale( const Aftr::VectorT<T>& scale )
{
   this->m[0]  = scale.x;
   this->m[5]  = scale.y;
   this->m[10] = scale.z;
}

template< typename T >
void Aftr::Mat4T<T>::multScale(const Aftr::VectorT<T>& scale)
{
   this->m[0] *= scale.x;
   this->m[5] *= scale.y;
   this->m[10] *= scale.z;
}

template< typename T >
T* Aftr::Mat4T<T>::getPtr()
{
   return this->m.data();
}

template< typename T >
const T* Aftr::Mat4T<T>::getPtr() const
{
   return this->m.data();
}

