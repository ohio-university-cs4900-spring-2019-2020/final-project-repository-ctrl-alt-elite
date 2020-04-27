#pragma once

#include <string>

namespace Aftr
{

   //think about templating this to use either floats or doubles?
   class Complex
   {
   public:
      Complex();
      Complex( double root );
      Complex( double real, double img );
      double real;
      double img;
      void setRealImg( double real, double img );
      //void setMagPhase
      void setRoot( double root );//sets the complex number to e^(-2pi*root*i)
      double magnitude();
      double phase();
      Complex operator*( const Complex& x )const;
      Complex operator/( double x )const;
      Complex operator+( const Complex& x )const;
      Complex operator-( const Complex& x )const;
      std::string toString()const;
      Complex conjugate();

      //add operators as needed
   };
}