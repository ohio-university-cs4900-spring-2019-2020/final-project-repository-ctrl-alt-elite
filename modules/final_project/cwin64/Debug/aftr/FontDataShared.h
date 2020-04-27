#pragma once

#include "AftrOpenGLIncludes.h"
#include <string>
#include <unordered_map>
//FreeType Headers
#ifdef AFTR_CONFIG_USE_FONTS
#include "ft2build.h"
#include FT_FREETYPE_H //Free type docs ask us to use macros to include its files for some reason
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_TRIGONOMETRY_H
//#include "freetype.h"
//#include "ftglyph.h"
//#include "ftoutln.h"
//#include "fttrigon.h"
#endif

namespace Aftr
{
   class AftrFrameBufferObject;

   struct CharcodeData
   {
      GLuint textureHandle;
      size_t charWidth;
      size_t charHeight;
      size_t charAdvance;
      int charTop;
   };

   class FontDataShared
   {
   public:
      FontDataShared( std::string& fontPath, size_t fontSize );
      virtual ~FontDataShared();
      bool operator <( const FontDataShared& tex ) const;
      void init();
      size_t getFontSize() { return fontSize; }
      std::string getFontPath() { return fontPath; }

      size_t maxWidth;
      size_t maxHeight;

      #ifdef AFTR_CONFIG_USE_FONTS
         FT_Face face;//Freetype face for this font
         FT_Library library;              
      CharcodeData& getCharcodeData( unsigned char x );///< returns the CharcodeData for a given character from the map if it exists; if not, it loads it
      #endif

      //bool isCached( const std::string& str );
      //void cacheString( const std::string& str, AftrFrameBufferObject* fbo );///< returns true if item is in cache, false otherwise

      //std::map< std::string, AftrFrameBufferObject* > cache;

   protected:
      std::string fontPath;
      size_t fontSize;
    
      #ifdef AFTR_CONFIG_USE_FONTS
      void loadCharacterTexture( FT_Face face, FT_ULong i );         
      std::unordered_map< FT_ULong, CharcodeData > mapOfCharcodeToOpenGLTextureHandle;
       #endif
   };
}

