#pragma once
#include "AftrConfig.h"
#include <iostream>
#include <memory>
#include "Mat4Fwd.h"
#include "BoundingBox.h"
#include "FontAlignments.h"

namespace ftgl { struct vertex_buffer_t; struct texture_atlas_t; struct texture_font_t;}

namespace Aftr
{
class GLSLShader;
class GLSLUniform;
class Camera;
class FTGLFontDataShared;
class Texture;

/**
   A String class that uses freetype-gl as well as freetype2 to render a text using signed distance maps..
   Each character gets one quad( 2 triangles ) and indexes into a texture atlas of contour data for consumption
   by the signed distance map shader.

   Any true-type font( .ttf ) may be loaded. Several MGLs (MGLFTGLString and MGLOverlayFTGLString) exist that 
   take ownership of a loaded std::unique_ptr<FTGLString> and enable it to be positioned and oriented via 
   a Model class.

   Example Usage:
   WO* wo = WO::New();
   wo->setLabel( "Font Text WO using Perspective Projection" );
   //Load DejaVuSansMono.ttf at font size 18.0. This information is encapsulated in an FTGLString object.
   std::unique_ptr< FTGLString > ftglString = FTGLString::New( ManagerEnvironmentConfiguration::getSMM() + "/fonts/DejaVuSansMono.ttf", 18.0f );
   //An MGLFTGL consumes an FTGLString object and uses it internally to render text at a desired position / orientation
   MGLFTGLString* mgl = MGLFTGLString::New( wo, std::move( ftglString ), 4.0f, 1.0f ); //wo is the MGL's parent
   mgl->setText( "Hello World..." );
   mgl->setPosition( { 20.0f, 15.f, 5.0f } );
   wo->setModel( mgl ); //Assign the MGL to the WO
   worldLst->push_back( wo );

*/
class FTGLString
{
public:
   static std::unique_ptr< FTGLString > New( const std::string& fileName, float fontSize = 18.0f );
   FTGLString() = delete;
   FTGLString( const FTGLString& toCopy ) = delete;
   FTGLString( FTGLString&& toMove ) = delete;
   virtual ~FTGLString();
   FTGLString& operator=( const FTGLString& toAssign ) = delete;
   FTGLString& operator=( FTGLString&& toMove ) = delete;

   virtual void render();
   Texture* getTextureCloneOfAtlas() const;

   const BoundingBox& getBoundingBox() const { return this->bbox; }
   /// Returns the offset from the string's center point to the center of the tightest bounding box fitting the string's text
   const Vector& getCenterOffsetSS() const { return this->ftglFontCenterOffsetScreenSpace; }
   /// Returns width of string in screen space [0,1]
   float getWidthSS() const { return this->widthScreenSpace; }
   /// Returns height of string in screen space [0,1]
   float getHeightSS() const { return this->heightScreenSpace; }
   
   /// Returns width of string in screen space in pixels [0,HorizontalResolution - 1]
   float getWidthSSPixels() const { return this->bbox.getlxlylz().x; }
   /// Returns height of string in screen space [0,VerticalResolution - 1]
   float getHeightSSPixels() const { return this->bbox.getlxlylz().y; }

   float getFontSize() const;
   std::string getFontPath() const;

   /// Fonts have their own aspect ratio to maximize readability.
   /// If FONT_ASPECT_RATIO_TYPE is set to FIXED_BY_WIDTH and the font is set to be 4 units wide, then
   /// the height of the font is dynamically adjusted to maintain the aspect ratio (FIXED_BY_WIDTH).
   ///
   /// If FONT_ASPECT_RATIO_TYPE is set to FIXED_BY_HEIGHT and the font is set to be 1.25 units high (tall), 
   /// the width of the font is dynamically adjusted to maintain the aspect ratio (FIXED_BY_HEIGHT).
   ///
   /// If FONT_ASPECT_RATIO_TYPE is set to FIXED_BY_WIDTH_AND_HEIGHT and the font is set to be 2.5 units wide
   /// and 10 units tall, neither the width nor height is scaled. The aspect ratio will not be maintained
   /// and readability may suffer, however, the font's bounding box will exactly fit the width and height.
   FONT_ASPECT_RATIO_TYPE getFontAspectRatioType() const { return this->aspectType; }

   /// Sets the font's aspect ratio type. This takes affect only after subsequent call to setText().
   /// Fonts have their own aspect ratio to maximize readability.
   /// If FONT_ASPECT_RATIO_TYPE is set to FIXED_BY_WIDTH and the font is set to be 4 units wide, then
   /// the height of the font is dynamically adjusted to maintain the aspect ratio (FIXED_BY_WIDTH).
   ///
   /// If FONT_ASPECT_RATIO_TYPE is set to FIXED_BY_HEIGHT and the font is set to be 1.25 units high (tall), 
   /// the width of the font is dynamically adjusted to maintain the aspect ratio (FIXED_BY_HEIGHT).
   ///
   /// If FONT_ASPECT_RATIO_TYPE is set to FIXED_BY_WIDTH_AND_HEIGHT and the font is set to be 2.5 units wide
   /// and 10 units tall, neither the width nor height is scaled. The aspect ratio will not be maintained
   /// and readability may suffer, however, the font's bounding box will exactly fit the width and height.
   void setFontAspectRatioType( FONT_ASPECT_RATIO_TYPE aspectType );

   //virtual float getWidthOfString( const std::string& str );
   //virtual float getHeightOfString( const std::string& str );

   //virtual void adjustForWidthOrientation(const std::string& label, FONT_ORIENTATION orientation, Mat4& modelMatrix) = 0;//adjusts the render position for the orientation using glTranslatef(), width orientation should be called on each line seperately
   //virtual void adjustForHeightOrientation(const std::string& label, FONT_ORIENTATION orientation, Mat4& modelMatrix) = 0;//adjusts the render position for the orientation using glTranslatef(), height orientation should be called on blocks of text together

   virtual void setText( const std::wstring& text );
   virtual void setText( const std::string& strText );
   virtual const std::wstring& getText() const;
   virtual std::wstring& getText();
   virtual std::string getTextASCII() const;
   //virtual std::string getText() const;

   /// This is used to compute the new width, height, and offset from center vector. This is commonly called when this string's
   /// text changes to a different size/length, and the bounding box / rendering quads need to be updated to have new size and
   /// offset dimensions. This is commonly called as a utility method by an MGL that is interested in rendering / orienting / positioning
   /// an FTGLString.
   static void computeWidthHeightAndOffsetBasedOnAspectRatioTypeAndTextLength(
                              FONT_ASPECT_RATIO_TYPE t, float widthPixelsSS, float heightPixelsSS, const Vector& currentFontCenterOffset,
                              float& inOutCurrentQuadWidth, float& inOutCurrentQuadHeight, Vector& outCurrentFontCenterOffset );

   ///Wraps an internal method that interfaces directly with FreeType GL to populate the VAO buffer w/ verts and texture
   ///coordinates. Typically the user would never need to call this unless they are doing something advanced.
   static void appendTextToBuffer( ftgl::vertex_buffer_t* buffer, ftgl::texture_font_t* font, const wchar_t* text, 
                                   const aftrColor4f& color, Vector& inOutPenStartAndEndPos, Aftr::BoundingBox* bbox );
      
protected:
   FTGLString( std::shared_ptr< FTGLFontDataShared >&& sharedData );

   std::wstring text = L"";

   ftgl::vertex_buffer_t* buffer = nullptr;
   std::shared_ptr< FTGLFontDataShared > fontShared = nullptr;
   BoundingBox bbox; ///< Contains current LxLy of text's bounding box, internally these units match FTGL's VAO, which is in pixels
   Vector ftglFontCenterOffsetScreenSpace = { 0, 0, 0 }; ///< Screen space position of the center of the font in range [0,1] in X and Y dims
   //Vector textLxLy;
   float widthScreenSpace = 0; ///< Screen space width [0,1]. Same as bbox.getlxlylz().x / ManagerWindowing::getScreenWidth().
   float heightScreenSpace = 0; ///< Screen space height [0,1]. Same as bbox.getlxlylz().y / ManagerWindowing::getScreenHeight().
   aftrColor4f color;// = { 1.0f, 1.0f, 1.0f, 1.0f };

   FONT_ASPECT_RATIO_TYPE aspectType = FONT_ASPECT_RATIO_TYPE::FIXED_BY_WIDTH;
      
};

}

