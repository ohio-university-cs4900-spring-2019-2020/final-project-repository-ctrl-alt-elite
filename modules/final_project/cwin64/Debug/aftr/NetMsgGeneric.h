#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

   class NetMsgGeneric : public NetMsg
   {
   public:
      NetMsgMacroDeclaration( NetMsgGeneric );

      NetMsgGeneric();
      virtual ~NetMsgGeneric();
      virtual bool toStream( NetMessengerStreamBuffer& os ) const;
      virtual bool fromStream( NetMessengerStreamBuffer& is );
      virtual void onMessageArrived();
      virtual std::string toString() const;

      std::string messageStrToCreate;

   protected:

   };

} //namespace Aftr

#endif
