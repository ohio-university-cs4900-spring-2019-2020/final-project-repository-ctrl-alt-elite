#pragma once

#include "MGL.h"

namespace ftgl { struct vertex_buffer_t; struct texture_atlas_t; struct texture_font_t; }

namespace Aftr
{

class IndexedGeometryQuad;
class Texture;
class FTGLString;
class GLSLShaderFontDistanceFieldGL32;

class MGLOverlayFTGLString : public MGL
{
public:
   static MGLOverlayFTGLString* New( WO* parentWO, std::unique_ptr< FTGLString > string, float width, float height );
   virtual ~MGLOverlayFTGLString();
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

   void setText( const std::string& text );
   void setText( const std::wstring& text );
   const std::wstring& getText() const;
   std::string getTextASCII() const;

   /// Sets the width and height of this Text in world units. The FontAspectRatioType may alter the specified
   /// width or height depending on if it is set to FIXED_BY_WIDTH, FIXED_BY_HEIGHT, or FIXED_BY_WIDTH_AND_HEIGHT.
   void setSize( float width, float height );

   void setFontColor( const aftrColor4f& color );

   FONT_ASPECT_RATIO_TYPE getFontAspectRatioType() const { return this->string->getFontAspectRatioType(); }
   void setFontAspectRatioType( const FONT_ASPECT_RATIO_TYPE& aspectType );

   /// Uses the current width, height, and font aspect type to adjust the bounding box, renderSelection quad,
   /// and ftglFontCenterOffset vector to properly fit, position, and render the current text within the string.
   /// This assumes the current frame buffer's dimensions have NOT changed since the previous call 
   /// (ie, ManagerWindowing::getScreenWidth()) has not changed. If a change has occurred, use MGLGUIFTGLString::onResizeWindow()
   void updateStringDimensions();
   
   /// Performs essentially the same job as updateStringDimensions, but ALSO recomputes sizes and offsets based on any change
   /// in the current frame buffer size (Window resize). ManagerWindowing::getScreenWidth() / Height() will be quiered to 
   /// obtain the new pixel height/width of screen.
   /// If no change in screen size has occurred, MGLGUIFTGLString::updateStringDimensions() requires less computation.
   void onResizeWindow();

   MGLOverlayFTGLString( const MGLOverlayFTGLString& toCopy ) = delete;
   MGLOverlayFTGLString( MGLOverlayFTGLString&& toMove ) = delete;
   MGLOverlayFTGLString& operator=( const MGLOverlayFTGLString& toCopyAssign ) = delete;
   MGLOverlayFTGLString& operator=( MGLOverlayFTGLString&& toMoveAssign ) = delete;
protected:
   MGLOverlayFTGLString( std::unique_ptr< FTGLString > string, float width, float height, WO* parentWO );
   virtual void onCreate( float width, float height );
   float height = 0; ///< Height of string's bounding box, relative to current frame buffer size in range [0,1]
   float width = 0; ///< Width of string's bounding box, relative to current frame buffer size in range [0,1]
   Vector ftglFontCenterOffset; ///< ftgl::Freetype fonts aren't perfectly centered about their vertices, to tightly fit them, this is computed when the text is modified
   IndexedGeometryQuad* quad = nullptr;
   std::unique_ptr< FTGLString > string = nullptr;
   GLSLShaderFontDistanceFieldGL32* fontShader = nullptr;
};

} //namespace Aftr

