#pragma once

#include "MGL.h"
#include "FontAlignments.h"

namespace ftgl { struct vertex_buffer_t; struct texture_atlas_t; struct texture_font_t; }

namespace Aftr
{

   class IndexedGeometryQuad;
   class Texture;
   class FTGLString;
   class GLSLShaderFontDistanceFieldGL32;

   /**
      A String class that uses freetype-gl as well as freetype2 to render a text via a FTGLString.
      Each character gets one quad (2 triangles) and indexes into a texture atlas of contour data for consumption
      by the signed distance map shader.

      Any true-type font (.ttf) may be loaded. The font is specified as a floating point value. The TTF must support
      the font size passed in or an error will occur.
   */
   class MGLFTGLString : public MGL
   {
   public:
      static MGLFTGLString* New( WO* parentWO, std::unique_ptr< FTGLString > string, float width, float height );
      virtual ~MGLFTGLString();
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

      void setText( const std::string& text );
      void setText( const std::wstring& text );
      const std::wstring& getText() const;
      std::string getTextASCII() const;

      void setFontColor( const aftrColor4f& color );

      /// Sets the width and height of this Text in world units. The FontAspectRatioType may alter the specified
      /// width or height depending on if it is set to FIXED_BY_WIDTH, FIXED_BY_HEIGHT, or FIXED_BY_WIDTH_AND_HEIGHT.
      void setSize( float width, float height );      

      FONT_ASPECT_RATIO_TYPE getFontAspectRatioType() const;
      void setFontAspectRatioType( const FONT_ASPECT_RATIO_TYPE& aspectType );

      /// Uses the current width, height, and font aspect type to adjust the bounding box, renderSelection quad,
      /// and ftglFontCenterOffset vector to properly fit, position, and render the current text within the string.
      void updateStringDimensions();

      MGLFTGLString( const MGLFTGLString& toCopy ) = delete;
      MGLFTGLString( MGLFTGLString&& toMove ) = delete;
      MGLFTGLString& operator=( const MGLFTGLString& toCopyAssign ) = delete;
      MGLFTGLString& operator=( MGLFTGLString&& toMoveAssign ) = delete;

   protected:
      MGLFTGLString( std::unique_ptr< FTGLString > string, float width, float height, WO* parentWO );
      virtual void onCreate( float width, float height );
      float height = 0; ///< Height of string's bounding box, in world space (automatically updated to keep aspect ratio of text consistent so fonts don't squish/stretch
      float width = 0; ///< Width of string's bounding box, in world space
      Vector ftglFontCenterOffset; ///< ftgl::Freetype fonts aren't perfectly centered about their vertices, to tightly fit them, this is computed when the text is modified
      IndexedGeometryQuad* quad = nullptr;
      std::unique_ptr< FTGLString > string = nullptr;
      GLSLShaderFontDistanceFieldGL32* fontShader = nullptr; ///< Signed Distance Map shader, also used to set font color
   };

} //namespace Aftr

