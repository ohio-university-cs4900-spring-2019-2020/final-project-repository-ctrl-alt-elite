#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

class NetMsgSendDataReply : public NetMsg
{
public:
   NetMsgMacroDeclaration( NetMsgSendDataReply );

   NetMsgSendDataReply();
   virtual ~NetMsgSendDataReply();
   virtual bool toStream( NetMessengerStreamBuffer& os ) const;
   virtual bool fromStream( NetMessengerStreamBuffer& is );
   virtual void onMessageArrived();
   virtual std::string toString() const;

   unsigned int woID;

protected:

};

} //namespace Aftr

#endif
