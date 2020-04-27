#pragma once

#include "ManagerSerializableNetMsgMap.h"
#include "NetMessengerStreamBuffer.h"
#include <string>

namespace Aftr
{

#define NetMsgMacroDeclaration( className ) \
   \
   /** Returns a string containing the actual name of this class */ \
   virtual std::string getClassName() const \
   { \
      return std::string( #className ); \
   } \
   \
   static NetMsg* createFromStream( NetMessengerStreamBuffer& is ); \
   \
   virtual unsigned int getNetMsgID() const \
   { \
      return ManagerSerializableNetMsgMap::getNetMsgID( #className ); \
   } \
   \
   class NetMsg_Serializable##className##Map \
   { \
      public: /*Declares stub class that registers fromFile function pointer w/ manager */ \
      NetMsg_Serializable##className##Map() { ManagerSerializableNetMsgMap::registerNetMsgType( #className, &(className::createFromStream) ); } \
   }; \
   \
   typedef className ThisClassType; /* Refers to the actual class declared*/


#define NetMsgMacroDefinition( className ) \
   className::NetMsg_Serializable##className##Map instanceWO_Serializeable##className##Map; \
   typedef className ThisClassType; /* Refers to the actual class declared*/ \
   \
   NetMsg* ThisClassType::createFromStream( NetMessengerStreamBuffer& is ) \
   { \
      ThisClassType* msg = new ThisClassType(); \
      if( msg->fromStream( is ) ) \
         return msg; \
      delete msg; msg = NULL; \
      return NULL; \
   }
   

} //namespace Aftr

