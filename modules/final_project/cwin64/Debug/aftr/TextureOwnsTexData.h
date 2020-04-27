#pragma once

#include "Texture.h"

namespace Aftr
{

class TextureOwnsTexData : public Texture
{
public:
   TextureOwnsTexData();
   TextureOwnsTexData( const TextureOwnsTexData& toCopy ) = delete;
   virtual ~TextureOwnsTexData();
   virtual Texture* cloneMe() = 0;

protected:

};

} //namespace Aftr
