#pragma once

#include <string>
#include <map>
#include <fstream>

namespace Aftr
{

   class AftrConfigurationParser
   {
   public:
      AftrConfigurationParser();
      static std::map<std::string, std::string> parseFile( const std::string& filename );
   protected:
      /**
   
      If a line begins with an '#', the pair <"",""> is not returned.

      If a line contains now '=', the pair <"",""> is returned.

      Otherwise the pair will contain <everything before first equal sign, everything after first equal sign>.

      */
      static std::pair<std::string, std::string> parseLine(std::ifstream& xin);
   };

}

