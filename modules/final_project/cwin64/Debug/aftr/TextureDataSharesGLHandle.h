#pragma once

#include "TextureData.h"

namespace Aftr
{

class TextureDataSharesGLHandle : public TextureData
{
public:

   TextureDataSharesGLHandle( const std::string& fileName );
   TextureDataSharesGLHandle( const GLuint* glTexPtr );

   /**
      This texture data shares the GL handle (for example, with an FBO), thus 
      when this instance is deleted, the corresponding data is NOT removed from OpenGL
   */
   virtual ~TextureDataSharesGLHandle();
   //virtual TextureData* cloneMe();

protected:

};

} //namespace Aftr

