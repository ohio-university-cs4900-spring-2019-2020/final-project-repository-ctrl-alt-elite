#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

   class NetMsgSendString : public NetMsg
   {
   public:
      NetMsgMacroDeclaration( NetMsgSendString );

      NetMsgSendString();
      virtual ~NetMsgSendString();
      virtual bool toStream( NetMessengerStreamBuffer& os ) const;
      virtual bool fromStream( NetMessengerStreamBuffer& is );
      virtual void onMessageArrived();
      virtual std::string toString() const;

      std::string message;
      static unsigned int getCount();
      static unsigned int getBytesRecvd();

   protected:

   };

} //namespace Aftr

#endif
