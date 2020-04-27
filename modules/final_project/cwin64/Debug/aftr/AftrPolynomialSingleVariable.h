#pragma once

#include <vector>
#include <string>

namespace Aftr
{

class AftrPolynomialSingleVariable
{
public:
   AftrPolynomialSingleVariable(){}
   AftrPolynomialSingleVariable(const std::vector<float>& x);
   ~AftrPolynomialSingleVariable(){}
   AftrPolynomialSingleVariable operator+(const AftrPolynomialSingleVariable& x);
   AftrPolynomialSingleVariable operator*(const AftrPolynomialSingleVariable& x);
   std::string toString();
   //std::vector
protected:
   std::vector<float> data;
};

}

