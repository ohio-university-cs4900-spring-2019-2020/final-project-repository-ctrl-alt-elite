#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

class NetMsgReplyOneFloat : public NetMsg
{
public:
   NetMsgMacroDeclaration(NetMsgReplyOneFloat);

   NetMsgReplyOneFloat();
   NetMsgReplyOneFloat(float f);
   virtual ~NetMsgReplyOneFloat();
   virtual bool toStream(NetMessengerStreamBuffer& os);
   virtual bool fromStream(NetMessengerStreamBuffer& is);
   virtual void onMessageArrived();
   virtual std::string toString() const;

   float f;

protected:

};

} //namespace Aftr

#endif
