#pragma once
#include <string>

namespace Aftr
{

class AftrFileIO
{
public:

   static bool readASCIIFile( const std::string& pathToFile, std::string& outFileContents );

};

}

