#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

class WOString : public WO
{
public:
   static WOString* New( const std::string& str, const std::string& fontPath, size_t fontSize, float worldSpaceHeight );
   virtual ~WOString(){}
   std::string getText();
protected:
   WOString();
   virtual void onCreate(const std::string& str, const std::string& fontPath, size_t fontSize, float worldSpaceHeight );
};

}

