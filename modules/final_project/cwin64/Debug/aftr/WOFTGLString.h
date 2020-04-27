#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

class WOFTGLString : public WO
{
public:
   static WOFTGLString* New( const std::string& fontPath, float fontSize );
   virtual ~WOFTGLString(){}
   std::string getText();
   void setText( const std::string& text );
   void setText( const std::wstring& text );
protected:
   WOFTGLString();
   virtual void onCreate( const std::string& fontPath, float fontSize );
};

}

