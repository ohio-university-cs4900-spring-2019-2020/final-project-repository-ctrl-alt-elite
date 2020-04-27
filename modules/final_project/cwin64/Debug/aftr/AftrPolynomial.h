/*
#pragma once

#include <map>
#include <string>

namespace Aftr
{

class AftrPolynomial
{
public:
   AftrPolynomial(const std::string&);
   std::string toString();
   AftrPolynomial operator*(const AftrPolynomial& x);
   AftrPolynomial operator+(const AftrPolynomial& x);
protected:
   std::map<std::string, float> data;
};

}

#endif
*/