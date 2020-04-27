#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "AftrGlobals.h"


namespace Aftr
{
/**
   \author Scott Nykl
   This class parses and XML content for the Abstract Forces associated with
   a specific graphical model (Typically a VRML model read in from file).
   /{
*/

enum class ABSTRACT_FORCE_TYPE { afBUOYANCY = 0, afTHRUSTER, afNUM_ABSTRACT_FORCE_TYPE };

class AbstractForceParser
{

public:
   AbstractForceParser( const std::string& abstractForceFileName, ABSTRACT_FORCE_TYPE type );
   virtual ~AbstractForceParser();
   bool isGoodInput() { return this->goodInput; }
   void getNext( std::vector< float >& ret );

protected:

   /**if true, file was successfully opened and ABSTRACT_FORCE_TYPE section
      was successfully located within the XML file. */
   bool goodInput;
   bool findType();
   bool isEndOfTypeSection( std::string& line );

   ABSTRACT_FORCE_TYPE type;

   std::ifstream* fs;

};

/**
   \}
*/

} //namespace Aftr
