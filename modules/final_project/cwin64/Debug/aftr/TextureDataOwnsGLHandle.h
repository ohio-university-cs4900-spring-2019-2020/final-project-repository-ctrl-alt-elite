#pragma once

#include "TextureData.h"

namespace Aftr
{

class TextureDataOwnsGLHandle : public TextureData
{
public:

   TextureDataOwnsGLHandle( const std::string& fileName );
   TextureDataOwnsGLHandle( const GLuint* glTexPtr );

   /**
      This texture data owns the GL handle, thus when this instance is
      deleted, the corresponding data is removed from OpenGL
   */
   virtual ~TextureDataOwnsGLHandle();
   //virtual TextureData* cloneMe();

protected:

};

} //namespace Aftr

