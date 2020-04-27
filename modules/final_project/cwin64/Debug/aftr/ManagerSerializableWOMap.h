#pragma once

#include <map>
#include <string>

namespace Aftr
{
class WO;
typedef WO* (*FuncPtrWOFromFile) ( std::istream& );

class ManagerSerializableWOMap
{
public:
   static void shutdownManager();
   static void registerWOType( const std::string& woType, FuncPtrWOFromFile funcPtrWOFromFile );
   static WO* createInstance( const std::string& woType, std::istream& sin );
   static bool retrieveStatementFromStream( std::istream& sin, std::string& lhs, std::string& rhs );

protected:
   static void init();
   static std::map< std::string, FuncPtrWOFromFile >* nameToFuncMap;
};

} //namespace Aftr

