#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

class NetMsgSendData : public NetMsg
{
public:
   NetMsgMacroDeclaration( NetMsgSendData );

   NetMsgSendData();
   virtual ~NetMsgSendData();
   virtual bool toStream( NetMessengerStreamBuffer& os ) const;
   virtual bool fromStream( NetMessengerStreamBuffer& is );
   virtual void onMessageArrived();
   virtual std::string toString() const;

   float xPos;
   float yPos;
   float zPos;

protected:

};

} //namespace Aftr

#endif
