#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

class NetMsgSendGLTexture : public NetMsg
{
public:
   NetMsgMacroDeclaration( NetMsgSendGLTexture );

   NetMsgSendGLTexture();
   virtual ~NetMsgSendGLTexture();
   virtual bool toStream( NetMessengerStreamBuffer& os ) const;
   virtual bool fromStream( NetMessengerStreamBuffer& is );
   virtual void onMessageArrived();
   virtual std::string toString() const;

   int horzPix{ 0 };
   int vertPix{ 0 };
   int numComponents{ 0 };
   int bytesPerComponent{ 0 };
   std::unique_ptr< uint8_t[] > dat = nullptr;

protected:

};

} //namespace Aftr

#endif
