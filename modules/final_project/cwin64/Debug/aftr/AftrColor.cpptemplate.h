namespace Aftr
{
   template< typename T, uint8_t C >
   AftrColorT<T, C>::AftrColorT()
   {
      for( auto& v : this->data )
         v = std::numeric_limits<T>::max();
   }

   template< typename T, uint8_t C >
   AftrColorT<T,C>::AftrColorT( std::initializer_list<T> colors )
   {
      if( colors.size() != C )
      {
         std::cout << "ERROR: " << AFTR_FILE_LINE_STR << ": AftrColorT<T,C>: User passed in wrong number of colors -- colors.size() ("
                   << colors.size() << ") != templated val (" << uint(C) << ")...\n";
         std::abort();
      }

      std::copy( colors.begin(), colors.end(), data.begin() );
   }

   template<typename T, uint8_t C>
   T& AftrColorT<T,C>::operator [] ( size_t i ) noexcept
   {
      if( i >= C )
      {
         std::cout << "ERROR: " << AFTR_FILE_LINE_STR << ": User tried to access color index " << i 
                   << ", but num color channels C was only " << uint( C ) << "...\n";
         std::abort();
      }
      return this->data[i];
   }

   template<typename T, uint8_t C>
   const T& AftrColorT<T, C>::operator [] ( size_t i ) const noexcept
   {
      if( i >= C )
      {
         std::cout << "ERROR: " << AFTR_FILE_LINE_STR << ": User tried to access color index " << i
                   << ", but num color channels C was only " << uint( C ) << "...\n";
         std::abort();
      }
      return this->data[i];
   }

   template<typename T, uint8_t C>
   bool AftrColorT<T, C>::operator ==( const AftrColorT<T,C>& c ) const noexcept
   {
      return std::equal( this->data.cbegin(), this->data.cend(), c.cbegin() );
   }

   template<typename T, uint8_t C>
   AftrColorT<T,C> AftrColorT<T, C>::operator+( const AftrColorT<T,C>& c ) const noexcept
   {
      AftrColorT<T, C> sum;
      std::transform( this->cbegin(), this->cend(), c.cbegin(), sum.begin(), std::plus<T>() );
      return sum;
   }

   template<typename T, uint8_t C>
   AftrColorT<T, C> AftrColorT<T, C>::operator+( const T& v ) const noexcept
   {
      AftrColorT<T, C> sum;
      std::transform( this->cbegin(), this->cend(), sum.begin(), [&v] ( const T& a ) { return a + v; } );
      return sum;
   }

   template<typename T, uint8_t C>
   AftrColorT<T, C>& AftrColorT<T, C>::operator+=( const AftrColorT<T, C>& c ) noexcept
   {
      std::transform( this->begin(), this->end(), c.cbegin(), this->begin(), std::plus<T>() );
      return *this;
   }

   template<typename T, uint8_t C>
   AftrColorT<T, C> AftrColorT<T, C>::operator-( const AftrColorT<T, C>& c ) const noexcept
   {
      AftrColorT<T, C> diff;
      std::transform( this->cbegin(), this->cend(), c.cbegin(), diff.begin(), std::minus<T>() );
      return diff;
   }

   template<typename T, uint8_t C>
   AftrColorT<T, C> AftrColorT<T, C>::operator-( const T& v ) const noexcept
   {
      AftrColorT<T, C> diff;
      std::transform( this->cbegin(), this->cend(), diff.begin(), [&v] ( const T& a ) { return a - v; } );
      return diff;
   }

   template<typename T, uint8_t C>
   AftrColorT<T, C>& AftrColorT<T, C>::operator-=( const AftrColorT<T, C>& c ) noexcept
   {
      std::transform( this->begin(), this->end(), c.cbegin(), this->begin(), std::minus<T>() );
      return *this;
   }

   template<typename T, uint8_t C>
   std::string AftrColorT<T, C>::toString() const noexcept
   {
      std::stringstream ss;
      ss << "[";
      for( int i = 0; i < C; ++i )
      {
         ss << data[i];
         if( i != C - 1 )
            ss << ",";
      }
      ss << "]";
      return ss.str();
   }
}
