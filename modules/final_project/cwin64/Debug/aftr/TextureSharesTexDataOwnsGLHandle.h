#pragma once

#include "TextureSharesTexData.h"

namespace Aftr
{

class TextureDataOwnsGLHandle;

class TextureSharesTexDataOwnsGLHandle : public TextureSharesTexData
{
public:
   TextureSharesTexDataOwnsGLHandle( TextureDataOwnsGLHandle* texData );
   TextureSharesTexDataOwnsGLHandle( const TextureSharesTexDataOwnsGLHandle& toCopy ) = delete;
   virtual ~TextureSharesTexDataOwnsGLHandle();
   virtual Texture* cloneMe();
protected:

};


} //namespace Aftr

