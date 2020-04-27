#pragma once

/// Forward declarations of the templated VectorT< typename T > class.
/// This is a convenience header file to forward declare the details describing a Vector and VectorD.
namespace Aftr
{
   template< typename T > class Mat4T;
   using Mat4 = Mat4T< float >;
   using Mat4D = Mat4T< double >;

} // namespace Aftr
