#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

class NetMsgShutdownInstance : public NetMsg
{
public:
   NetMsgMacroDeclaration( NetMsgShutdownInstance );

   NetMsgShutdownInstance();
   virtual ~NetMsgShutdownInstance();
   virtual bool toStream( NetMessengerStreamBuffer& os ) const;
   virtual bool fromStream( NetMessengerStreamBuffer& is );
   virtual void onMessageArrived();

protected:

};

} //namespace Aftr

#endif
