#pragma once

#include <string>
#include <vector>

namespace Aftr
{

/**
   This file include macro definitions that are used for any AftrLogData subclass. There are two macros.

   AftrLogDataMacroDeclaration( className ):
   
   The first macro is AftrLogDataMacroDeclaration( className ). This must be placed in the subclass's 
   header file in the public section. The parameter 'className' must be the exact name of the subclass
   as defined in the subclasses header file. This macro inserts 5 static method declarations:
   1) vector< className* >* fromFile( fileName )... Returns all data stored in fileName.
   2) bool toFile( vector< className* >* data, string fileName )... Appends data to filename
   3) fromStreamOneDatum... Helper method used by fromFile - retrieves exactly one datum from the stream
   4) toStreamOneDatum... Helper method used by toFile - writes exactly one datum to the stream
   5) string getClassName()... Returns a string exactly matching parameter className.
   
   Also, this macro declares a typedef called ThisClassType. The corresponding .cpp file will implement
   these 5 methods; however, instead of using the value of className, the typdef ThisClassType will be used
   instead. By doing this, copy/pasting the implementation into additional logging subclasses does not require
   changing any class names; it only requires changing the implementation of methods 3 and 4 above.

   
   AftrLogDataMacroDefinition( className ):

   The second macro is AftrLogDataMacroDefinition( className ). This must be placed in the subclass's 
   implementation file. The parameter 'className' must be the exact name of the subclass defined in the
   header file. This macro defines the typedef ThisClassType which refers to the value of className. The
   implementation of the 5 methods defined in the header file by this macro use ThisClassType and
   it is recommended that the implementation of these 5 methods use ThisClassType to refer to the class
   name. This way, additional logger subclasses only require copy/pasting this code and changing ONLY
   the implementation of methods 3 and 4 above. No refactoring of any class names need to occur for
   the above 5 methods - except for passing the new class name into the MacroDeclaration and MacroDefinition
   in the .h and .cpp, respectively.

   This is similar to a templated class; however, a templated class in C++ does not enable the fromFile()
   methods to create an instance of the template argument and invoke any class-defined methods defined on
   that instance. A template cannot enforce that any template parameter is a subclass of the AftrLogData
   instance and hence contains certain methods. Therefore, the base fromFile cannot implement code like this:

   std::vector< ThisClassType* >* d = new std::vector< ThisClassType* >();
   ThisClassType* datum = ThisClassType::fromStreamOneDatum( inputStream );
   d->push_back( datum );

   without the ThisClassType typedef.

*/
#define AftrLogDataMacroDeclaration( className ) \
\
static std::vector< className* >* fromFile( const std::string& fileName ); \
static bool toFile( std::vector< className* >* data, const std::string& fileName ); \
static className* fromStreamOneDatum( std::istream& is ); \
static bool toStreamOneDatum( className* d, std::ostream& os ); \
\
/** Returns a string containing the actual name of this class */ \
static std::string getClassName() \
{ \
   return std::string( #className ); \
} \
\
typedef className ThisClassType; /* Refers to the actual class declared*/ 



#define AftrLogDataMacroDefinition( className ) \
typedef className ThisClassType; /* Refers to the actual class declared*/

} //namespace Aftr

