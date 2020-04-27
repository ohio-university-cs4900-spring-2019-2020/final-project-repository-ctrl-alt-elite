#pragma once

#include "Texture.h"

namespace Aftr
{

class TextureSharesTexData : public Texture
{
public:
   TextureSharesTexData();
   TextureSharesTexData( const TextureSharesTexData& toCopy ) = delete;

   virtual ~TextureSharesTexData();
   virtual Texture* cloneMe() = 0;

protected:

};

} //namespace Aftr
