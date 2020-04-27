#pragma once

#include "FontDataShared.h"
#include "Font.h"
#include <string>
#include <set>

namespace Aftr
{
   
   class Font;

   struct FontSetCompare
   {
      bool operator() ( const FontDataShared* lhs, const FontDataShared* rhs ) const
      { 
         return ( (*lhs) < (*rhs) );
      }
   };

   class ManagerFont
   {
   public:
      static void init();
      static void shutdown();
      static Font* loadFont( const std::string& fontPath = std::string(""), size_t size = 18);
   protected:
      static std::set< FontDataShared*, FontSetCompare > fonts;
   };

}

