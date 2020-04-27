#pragma once
#include <limits>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>
#include "AftrConfig.h"

namespace Aftr
{

   //To compile AftrColorTest.cpp:
   //g++ --std=c++17 -I../../cwin64/ -I./ AftrColorTest.cpp

///Color that can be templated based on underlying storage and number of channels
///For example, an aftrColor4ub is actually a AftrColor<GLubyte,4>...
template <typename T, uint8_t C = 4 >
class AftrColorT
{
public:
   using value_type = T;
   using iterator = T*;
   constexpr static uint num_channels = C; ///< Number of color channels in this instance
   using const_iterator = const T*;

   //Iterators -- work with std::begin() / std::end()
   iterator begin()        noexcept       { return &this->data[0]; }
   const_iterator cbegin() const noexcept { return &this->data[0]; }
   iterator end()          noexcept       { return &this->data[C]; }
   const_iterator cend()   const noexcept { return &this->data[C]; }
   
   std::array<T, C> data;
   constexpr T& r() const noexcept { return data[0]; }
   constexpr T& r() noexcept       { return data[0]; }
   constexpr T& g() const noexcept { return data[1]; }
   constexpr T& g() noexcept       { return data[1]; }
   constexpr T& b() const noexcept { return data[2]; }
   constexpr T& b() noexcept       { return data[2]; }
   constexpr T& a() const noexcept { return data[3]; }
   constexpr T& a() noexcept       { return data[3]; }
   //T& r = data[0]; ///< R,G,B,A, respectively are simple accessors to access colors
   //T& g = data[1]; ///< R,G,B,A, respectively are simple accessors to access colors
   //T& b = data[2]; ///< R,G,B,A, respectively are simple accessors to access colors
   //T& a = data[3]; ///< R,G,B,A, respectively are simple accessors to access colors

   AftrColorT();
   AftrColorT( const AftrColorT& toCopy ) = default;
   ~AftrColorT() = default;
   AftrColorT& operator=( const AftrColorT& toAssign ) = default;

   std::string toString() const noexcept;

   //AftrColorT( T... C_number_of_Ts ) {};
   AftrColorT( std::initializer_list<T> );

   T& operator [] ( size_t i ) noexcept;
   const T& operator [] ( size_t i ) const noexcept;
   bool operator ==( const AftrColorT<T,C>& toCompare ) const noexcept;
   AftrColorT<T,C> operator+( const AftrColorT<T,C>& c ) const noexcept; ///< Adds two colors
   AftrColorT<T,C> operator+( const T& v ) const noexcept; ///< Adds v to each component
   AftrColorT<T,C> operator-( const AftrColorT<T,C>& c ) const noexcept; ///< Subtracts two colors
   AftrColorT<T,C> operator-( const T& v ) const noexcept; ///< Subtracts v from each component
   AftrColorT<T,C>& operator+=( const AftrColorT<T,C>& c ) noexcept;
   AftrColorT<T,C>& operator-=( const AftrColorT<T,C>& c ) noexcept;

   friend std::ostream& operator<<( std::ostream& out, const AftrColorT& v )
   {
      out << v.toString();
      return out;
   }

   friend AftrColorT<T, C> operator+( const T& v, const AftrColorT& c ) noexcept { return c + v; }

   //This method shouldn't exist... Subtracting a vector from a scalar makes little sense. The opposite
   //case, however, has an intuitive meaning -- that is, subtracting a scalar from a vector simply is
   //piece-wise per-component subtraction between each vector component and the scalar.
   //friend AftrColorT<T, C>& operator-=( const T& v, const AftrColorT& c ) noexcept { return c - v; }
};




using aftrColor4ub = AftrColorT<uint8_t, 4>;

}
#include "AftrColor.cpptemplate.h"
