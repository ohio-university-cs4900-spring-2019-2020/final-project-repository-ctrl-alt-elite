#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

class WOOverlayString : public WO
{
public:
   static WOOverlayString* New( const std::string& str, const std::string& fontPath, size_t fontSize );
   virtual ~WOOverlayString(){}
protected:
   WOOverlayString();
   virtual void onCreate( const std::string& str, const std::string& fontPath, size_t fontSize );
};

}

