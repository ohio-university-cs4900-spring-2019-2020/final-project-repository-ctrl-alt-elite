#pragma once

#include <string>

namespace Aftr
{

#define WOMacroDeclaration( className, superClassName ) \
\
/** Returns a string containing the actual name of this class */ \
static std::string getClassName() \
{ \
   return std::string( #className ); \
} \
  \
/** Returns a string containing the actual name of this class inherits from */ \
static std::string getSuperClassName() \
{ \
   return std::string( #superClassName ); \
} \
  \
class WO_Serializable##className##Map \
{ \
public: /*Declares stub class that registers fromFile function pointer w/ manager */ \
   WO_Serializable##className##Map() { ManagerSerializableWOMap::registerWOType( #className, &(className::fromFile) ); } \
}; \
typedef className ThisClassType; /* Refers to the actual class declared*/ \
typedef superClassName SuperClassType; /* Refers to the parent class inherited from*/



#define WOMacroDefinition( className, superClassName ) \
   className::WO_Serializable##className##Map instanceWO_Serializeable##className##Map; \
   typedef className ThisClassType; /* Refers to the actual class declared*/ \
   typedef superClassName SuperClassType; /* Refers to the parent class inherited from*/

} //namespace Aftr

