#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS
#include <string>

namespace ftgl { struct vertex_buffer_t; struct texture_atlas_t; struct texture_font_t; }

namespace Aftr
{

class Texture;

class FTGLFontDataShared
{
   friend class ManagerFTGLFont;

public:
   FTGLFontDataShared( const FTGLFontDataShared& toCopy ) = delete;
   FTGLFontDataShared( FTGLFontDataShared && toMove ) = delete;
   FTGLFontDataShared& operator=( const FTGLFontDataShared& toAssign ) = delete;
   FTGLFontDataShared& operator=( FTGLFontDataShared&& toMoveAssign ) = delete;
   virtual ~FTGLFontDataShared();

   std::string toString() const;

   Texture& getAtlasTexture();
   const Texture& getAtlasTexture() const;
   
   ftgl::texture_font_t* getFont();
   const ftgl::texture_font_t* getFont() const;

   ftgl::texture_atlas_t* getAtlas();
   const ftgl::texture_atlas_t* getAtlas() const;

protected:
   FTGLFontDataShared();
   Texture* fontTex = nullptr;
   ftgl::texture_font_t* font = nullptr;
   ftgl::texture_atlas_t* atlas = nullptr;

};

std::ostream& operator<<( std::ostream& os, const FTGLFontDataShared& fds );

}

#endif
