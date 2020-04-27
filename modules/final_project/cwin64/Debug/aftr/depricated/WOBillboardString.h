#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

class WOBillboardString : public WO
{
public:
   static WOBillboardString* New(const std::string& str, const std::string& fontPath, size_t fontSize);
   virtual ~WOBillboardString(){}
protected:
   WOBillboardString();
   virtual void onCreate(const std::string& str, const std::string& fontPath, size_t fontSize);
};

}

