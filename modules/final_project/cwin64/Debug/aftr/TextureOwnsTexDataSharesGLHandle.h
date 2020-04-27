#pragma once

#include "TextureOwnsTexData.h"

namespace Aftr
{

class TextureDataSharesGLHandle;

class TextureOwnsTexDataSharesGLHandle : public TextureOwnsTexData
{
public:
   TextureOwnsTexDataSharesGLHandle( TextureDataSharesGLHandle* texData );
   TextureOwnsTexDataSharesGLHandle( const TextureOwnsTexDataSharesGLHandle& toCopy ) = delete;
   virtual ~TextureOwnsTexDataSharesGLHandle();
   virtual Texture* cloneMe();
protected:

};


} //namespace Aftr

