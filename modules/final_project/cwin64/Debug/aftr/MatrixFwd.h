#pragma once

/// Forward declarations of the templated VectorT< typename T > class.
/// This is a convenience header file to forward declare the details describing a Vector and VectorD.
namespace Aftr
{
   template< typename T > class MatrixT;
   using Matrix = MatrixT< float > ;
   using MatrixD = MatrixT < double > ;

} // namespace Aftr
