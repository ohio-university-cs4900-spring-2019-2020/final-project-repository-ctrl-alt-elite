#pragma once

#include "TextureOwnsTexData.h"

namespace Aftr
{

class TextureDataOwnsGLHandle;

class TextureOwnsTexDataOwnsGLHandle : public TextureOwnsTexData
{
public:
   TextureOwnsTexDataOwnsGLHandle( TextureDataOwnsGLHandle* texData );
   virtual ~TextureOwnsTexDataOwnsGLHandle();
   virtual Texture* cloneMe();
protected:

};


} //namespace Aftr

