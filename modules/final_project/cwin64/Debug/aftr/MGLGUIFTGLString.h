#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS

#include "MGLGUI.h"
#include "FontAlignments.h"
#include <string>


namespace Aftr
{

class FTGLString;
class GLSLShaderFontDistanceFieldGL32;

class MGLGUIFTGLString : public MGLGUI
{
public:
   static MGLGUIFTGLString* New( WO* parent, const std::string& label );
   virtual ~MGLGUIFTGLString();
   virtual void render( const Camera& cam );
      
   void setText( const std::string& text );
   void setText( const std::wstring& text );
   const std::wstring& getText() const;
   std::string getTextASCII() const;
   

   void setColor( const aftrColor4f& color );

   /// Sets the width and height of this Text in world units. The FontAspectRatioType may alter the specified
   /// width or height depending on if it is set to FIXED_BY_WIDTH, FIXED_BY_HEIGHT, or FIXED_BY_WIDTH_AND_HEIGHT.
   void setSize( float width, float height );

   FONT_ASPECT_RATIO_TYPE getFontAspectRatioType() const;
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

   virtual void updateStencilBoundingQuad( bool stencilOpINCorDEC, GLubyte red = 255, GLubyte green = 255, GLubyte blue = 255 );
   virtual void isUsingStencilBuffer( bool useStencilBufferForClipping );

   float getWidthAbs() const;
   float getHeightAbs() const;

   /// This method must also replace this MGL's skin's multitextureSet[0] to point at 
   /// the SDM Font Texture specific to the new font path and font size.
   void setFontAndSize( const std::string& fontPath, float fontSize );
   void setFont( const std::string& fontPath );
   void setSize( float fontSize ); ///< Set's the size of the font

   void setFontOrientation( FONT_ORIENTATION orientation );
   void setFontJustification( FONT_JUSTIFICATION justification );

   MGLGUIFTGLString( const MGLGUIFTGLString& toCopy ) = delete;
   MGLGUIFTGLString( MGLGUIFTGLString&& toMove ) = delete;
   MGLGUIFTGLString& operator=( const MGLGUIFTGLString& toCopyAssign ) = delete;
   MGLGUIFTGLString& operator=( MGLGUIFTGLString&& toMoveAssign ) = delete;
      
protected:
   MGLGUIFTGLString( WO* parent, const std::string& label );
   virtual void onCreate();

   //////Inherited from MGLGUI: float height = 0; ///< Height of string's bounding box, in world space (automatically updated to keep aspect ratio of text consistent so fonts don't squish/stretch
   //////Inherited from MGLGUI: float width  = 0; ///< Width of string's bounding box, in world space
   Vector ftglFontCenterOffset; ///< ftgl::Freetype fonts aren't perfectly centered about their vertices, to tightly fit them, this is computed when the text is modified
   std::unique_ptr< FTGLString > string = nullptr;
   GLSLShaderFontDistanceFieldGL32* fontShader = nullptr;

   FONT_ORIENTATION fontOrientation = FONT_ORIENTATION::foCENTER;
   FONT_JUSTIFICATION fontJustification = FONT_JUSTIFICATION::fjCENTER;
};

}

#endif
