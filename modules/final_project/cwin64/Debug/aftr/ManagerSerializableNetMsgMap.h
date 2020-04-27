#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <map>
#include "NetMessengerStreamBuffer.h"

namespace Aftr
{
   class NetMsg;
   typedef NetMsg* (*FuncPtrNetMsgFromStream) ( NetMessengerStreamBuffer& );

   class ManagerSerializableNetMsgMap
   {
   public:
      static void shutdownManager();
      static void registerNetMsgType( const std::string& netMsgStr, FuncPtrNetMsgFromStream funcPtrNetMsgFromStream );
      static NetMsg* createInstance( unsigned int netMsgID, NetMessengerStreamBuffer& is );
      static bool isValidHeader( unsigned int netMsgID );
      
      /// Returns the corresponding unsigned int that is sent across the wire to identify
      /// NetMessage of type className. Returns 0 if an invalid className is passed in.
      /// The first valid ID begins with 1.
      static unsigned int getNetMsgID( const std::string& className );

   protected:
      static void init();
      static unsigned int getStringHash( const std::string& str );
      static bool hashCollisionExists( const std::string& newClassName );
      static std::map< unsigned int, FuncPtrNetMsgFromStream >* idToFuncMap; ///< Maps NetMsgID to create method
      static std::map< std::string, unsigned int >* stringToNameMap; ///< Maps string of NetMsgID class name to its NetMsgID
   };

} //namespace Aftr

#endif
