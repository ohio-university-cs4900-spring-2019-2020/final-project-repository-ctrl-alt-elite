
template< typename T >
Aftr::QuatT<T>::QuatT()
{
   a = 1;
   b = c = d = 0;
}

template< typename T >
Aftr::QuatT<T>::QuatT(T a, T b, T c, T d)
{
   this->a = a;
   this->b = b;
   this->c = c;
   this->d = d;
}

template< typename T >
Aftr::QuatT<T>::QuatT( const Aftr::QuatT<T>& toCopy )
{
   *this = toCopy;
}

template< typename T >
Aftr::QuatT<T>& Aftr::QuatT<T>::operator=( const Aftr::QuatT<T>& q )
{
   if( this != &q )
   {
      this->a = q.a;
      this->b = q.b;
      this->c = q.c;
      this->d = q.d;
   }
   return *this;
}

template< typename T >
Aftr::QuatT<T>::QuatT( const Mat4T<T>& dcm ) : Aftr::QuatT<T>( dcm.getPtr() ) {}

template< typename T >
Aftr::QuatT<T>::QuatT( const T* m )
{
   T trace = m[0] + m[5] + m[10] + m[15];
   if(trace > .000001)
   {
      T s = sqrt(trace) * 2;
      this->b = ( m[9] - m[6] ) / s;
      this->c = ( m[2] - m[8] ) / s;
      this->d = ( m[4] - m[1] ) / s;
      this->a = .25f * s;
   }
   else if(m[0] > m[5] && m[0] > m[10])
   {
      T s = sqrt(1 + m[0] - m[5] - m[10]);
      this->b = .25f * s;
      this->c = (m[4] + m[1]) / s;
      this->d = (m[2] + m[8]) / s;
      this->a = (m[9] - m[6]) / s;
   }
   else if(m[5] > m[10])
   {
      T s = sqrt( 1 + m[5] - m[0] - m[10] );
      this->b = (m[4] + m[1]) / s;
      this->c = .25f * s;
      this->d = (m[9] + m[6]) / s;
      this->a = (m[2] - m[8]) / s;
   }
   else
   {
      T s = sqrt(1 + m[10] - m[0] - m[5]);
      this->b = (m[2] + m[8]) / s;
      this->c = (m[9] + m[6]) / s;
      this->d = .25f * s;
      this->a = (m[4] - m[1]) / s;
   }
   normalize();
}

template< typename T >
Aftr::QuatT<T>::~QuatT()
{
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::negation() const
{
   Aftr::QuatT<T> temp(-a, -b, -c, -d);
   return temp;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::conjugation() const
{
   Aftr::QuatT<T> temp(a, -b, -c, -d);
   return temp;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::operator +(const Aftr::QuatT<T> &q) const
{
   Aftr::QuatT<T> temp(a + q.a, b + q.b, c + q.c, d + q.d);
   return temp;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::operator -(const Aftr::QuatT<T> &q) const
{
   Aftr::QuatT<T> temp(a - q.a, b - q.b, c - q.c, d - q.d);
   return temp;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::operator *(const Aftr::QuatT<T> &q) const
{
   //Exactly the same operations as a grassProduct
   //Qr = Qa * Qb
   //Calculates the combined rotation

   Aftr::QuatT<T> temp( a * q.a - b * q.b - c * q.c - d * q.d,
                           a * q.b + b * q.a + c * q.d - d * q.c,
                           a * q.c - b * q.d + c * q.a + d * q.b,
                           a * q.d + b * q.c - c * q.b + d * q.a );
   return temp;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::grassmanProduct(const Aftr::QuatT<T> &q) const
{     
   Aftr::QuatT<T> temp( a * q.a - b * q.b - c * q.c - d * q.d,
                           a * q.b + b * q.a + c * q.d - d * q.c,
                           a * q.c - b * q.d + c * q.a + d * q.b,
                           a * q.d + b * q.c - c * q.b + d * q.a );
   return temp;
}

template< typename T >
T Aftr::QuatT<T>::innerProduct(const Aftr::QuatT<T> &q) const
{
   return a * q.a + b * q.b + c * q.c + d * q.d;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::outerProduct(const Aftr::QuatT<T> &q) const
{
   Vector a(this->b, this->c, this->d);
   Vector b(q.b, q.c, q.d);
   Vector c;

   c = b * this->a;
   c = c - (a * q.a);
   c = c - a.crossProduct(b);

   Aftr::QuatT<T> temp(0, c.x, c.y, c.z);
   return temp;
}

template< typename T >
T Aftr::QuatT<T>::magnitude() const
{
   return sqrt( a * a + b * b + c * c + d * d );
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::crossProduct(const Aftr::QuatT<T> &q) const
{
   Vector a(this->b, this->c, this->d);
   Vector b(q.b, q.c, q.d);
   Vector c = a.crossProduct(b);

   Aftr::QuatT<T> temp(0, c.x, c.y, c.z);
   return temp;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::evenProduct(const Aftr::QuatT<T> &q) const
{

   QuatT temp(a * q.a - b * q.b - c * q.c - d * q.d,
      a * q.b + q.a * b,
      a * q.c + q.a * c,
      a * q.d + q.a * d);
   return temp;
}

template< typename T >
void Aftr::QuatT<T>::toRepresentationMatrix(T m[]) const
{
   m[0] = m[5] = m[10] = m[15] = a;
   m[1] = m[14] = b;
   m[2] = m[7] = c;
   m[3] = m[9] = d;
   m[4] = m[11] = -b;
   m[6] = m[12] = -d;
   m[8] = m[13] = -c;
}

template< typename T >
void Aftr::QuatT<T>::toRotationMatrix(T m[]) const
{
   m[3] = m[7] = m[11] = 0;
   m[12] = m[13] = m[14] = 0;
   m[15] = 1;
   m[0] = a * a + b * b - c * c - d * d;
   m[1] = 2 * b * c - 2 * a * d;
   m[2] = 2 * a * c + 2 * b * d;
   m[4] = 2 * a * d + 2 * b * c;
   m[5] = a * a - b * b + c * c - d * d;
   m[6] = 2 * c * d - 2 * a * b;
   m[8] = 2 * b * d - 2 * a * c;
   m[9] = 2 * a * b + 2 * c * d;
   m[10] = a * a - b * b - c * c + d * d;
}

template< typename T >
Aftr::Mat4T<T> Aftr::QuatT<T>::toRotationMatrix() const
{
   Aftr::Mat4T<T> m;
   this->toRotationMatrix( m.getPtr() );
   return m;
}

template< typename T >
std::string Aftr::QuatT<T>::toString() const
{
   std::stringstream ss;
   ss.precision( 3 );
   ss << "[" << this->a << ", " << this->b << "i, " << this->c << "j, " << this->d << "k]";
   return ss.str();
}

template< typename T >
void Aftr::QuatT<T>::normalize()
{
   T mag = this->magnitude();
   a /= mag;
   b /= mag;
   c /= mag;
   d /= mag;
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::normalizeMe() const
{
   T mag = this->magnitude();

   T w = a / mag;
   T x = b / mag;
   T y = c / mag;
   T z = d / mag;

   return QuatT( w,x,y,z );
}

template< typename T >
Aftr::QuatT<T> Aftr::QuatT<T>::slerp( const Aftr::QuatT<T>& startOrient, const Aftr::QuatT<T>& endOrient, T t )
{
   //T srcm[16];
   //T daftr[16];
   //aftrSetIdentityMatrix( srcm );
   //aftrSetIdentityMatrix( daftr );

   //AftrCoordinateTransforms::rotateAboutArbitraryAxis( Vector(0,1,0), 35.0f * Aftr::DEGtoRAD, daftr );
   //AftrCoordinateTransforms::rotateAboutArbitraryAxis( Vector(0,0,1), 90.0f * Aftr::DEGtoRAD, daftr );



   //QuatT thisQuat( srcm );
   //QuatT input( daftr );
   //std::cout << "src   quat " << thisQuat.toString() << "...\n";
   //std::cout << "input quat " << input.toString() << "...\n";

   //for( size_t i = 0; i < 101; ++i )
   //{
   //   T t = (T)i / (T)100;

   Aftr::QuatT<T> a = startOrient.normalizeMe();
   Aftr::QuatT<T> b = endOrient.normalizeMe();


   //std::cout << "A norm is " << a.toString() << "...\n";
   //std::cout << "B norm is " << b.toString() << "...\n";

   //compute "cosine of the angle" between quaternions using dot product
   T cosOmega = a.innerProduct( b );

   //if negative dot prod, negate one of input quaternions
   if( cosOmega < 0.0f )
   {
      b = b.negation();
      cosOmega *= -1.0f;
   }

   T k0 = 0.0f;
   T k1 = 1.0f;

   if( cosOmega > 0.9999f )
   {
      //very close to 1 (causes a divide by zero) - just use linear interpolation
      k0 = 1.0f - t;
      k1 = t;
   }
   else
   {
      //compute the sin of the angle using
      //trig identity sin^2 x + cos^2 x = 1
      T sinOmega = std::sqrt( 1.0f - cosOmega * cosOmega );

      //Compute the angle from its sin and cosine
      T omega = atan2f( sinOmega, cosOmega );

      //compute inverse of denominator, so we only divide once
      T oneOverSinOmega = 1.0f / sinOmega;

      //Compute interpolation parameters
      k0 = sinf( (1.0f - t) * omega ) * oneOverSinOmega;
      k1 = sinf( t * omega ) * oneOverSinOmega;
   }

   //Interpolate
   Aftr::QuatT<T> c( a.a * k0 + b.a * k1,
      a.b * k0 + b.b * k1,
      a.c * k0 + b.c * k1,
      a.d * k0 + b.d * k1 );
   c.normalize();
   //std::cout << "Interpolated quat is " << c.toString() << "...\n";

   //T m[16];
   //aftrSetIdentityMatrix( m );
   //c.toRotationMatrix( m );
   ////std::cout << "matrix version of quat is \n" << print4x4MatrixColumn( m ) << "\n";
   //T v[4] = {1,0,0,0};
   //T vout[4] = {0,0,0,0};

   //multiply4x4MatrixBy4x1Vector( m, v, vout );

   ////AftrAffine

   //Vector xdir( vout[0], vout[1], vout[2] );
   //Vector rpy = AftrCoordinateTransforms::transformFromDisplayMatrixToRollPitchYaw( m ).toVecS();

   //std::cout << "t " << t << ": " << xdir.toString() << " length is " << xdir.magnitude() << ", rpy is " << rpy.toString()  << "...\n";
   //}

   return c;
}
