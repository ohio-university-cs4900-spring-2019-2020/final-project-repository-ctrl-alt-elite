#pragma once
#include "AftrConfig.h"
#include "IndexedGeometryQuad.h"
#include <string>
#ifdef AFTR_CONFIG_USE_FONTS
#include "AftrGlobals.h"
#include "ft2build.h"
#include FT_FREETYPE_H //Free type docs ask us to use macros to include its files for some reason
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_TRIGONOMETRY_H
#endif

#include "Mat4Fwd.h"
#include "Font.h"
#include "GLSLShaderFont40.h"

namespace Aftr 
{

   class Font40 : public Font
   {
   public:
      Font40(FontDataShared* fontDataShared);
      virtual ~Font40();
      //the expected output of print is a quad of size getWidth by getHeight in whatever coordinate system you are using
     // virtual void print(const std::string& str, const Mat4& modelMatrix, const Camera& cam, FONT_ORIENTATION orientation = FONT_ORIENTATION::foCENTER, bool useCache = true, QuadOrientation qo = QuadOrientation::qoXY, FONT_JUSTIFICATION justification = FONT_JUSTIFICATION::fjCENTER);
    
      void adjustForWidthJustification(const std::string& label, float maxWidth, FONT_JUSTIFICATION justification);
   
      virtual void adjustForWidthOrientation(const std::string& label, FONT_ORIENTATION orientation, Mat4& modelMatrix);//adjusts the render position for the orientation by manipulating modelMatrix, width orientation should be called on each line seperately
      virtual void adjustForHeightOrientation(const std::string& label, FONT_ORIENTATION orientation, Mat4& modelMatrix);//adjusts the render position for the orientation by manipulating modelMatrix, height orientation should be called on blocks of text together

   
   protected:
      Font40() = delete;
      //FontDataShared* dataShared = nullptr;
      void printCachedString(const std::string& str, const Camera& cam, FONT_ORIENTATION orientation, QuadOrientation qo);
      void printUncachedString(const std::string& str, const Camera& cam, FONT_ORIENTATION orientation, FONT_JUSTIFICATION justification = FONT_JUSTIFICATION::fjCENTER, float madWidth = 0);
      void cacheString(const std::string& str, const Camera& cam, FONT_ORIENTATION orientation);
    
      GLSLShaderFont40* myShader;
     
      //4.0+ rendering
      void init();//initializes the vao
      GLuint vao = -1;
      GLuint vertexLocation = -1;
      GLuint textureLocation = -1;
      GLuint vertexBuffer = -1;
      GLuint textureBuffer = -1;
      GLuint indexBuffer = -1;
      virtual void printUncachedString(const std::string& str, Mat4& modelMatrix, const Camera& cam, FONT_ORIENTATION orientation, FONT_JUSTIFICATION justification = FONT_JUSTIFICATION::fjCENTER, float madWidth = 0);
      virtual void renderCharacter(unsigned char charcode, Mat4& modelMatrix, const Camera& cam);///< renders an individual character
      //actually rendering methods, forked in print()
       virtual void print(const std::string& str, const Mat4& modelMatrix, const Camera& cam, FONT_ORIENTATION orientation, bool useCache, Aftr::QuadOrientation qo, FONT_JUSTIFICATION justifcation, const std::vector< std::string >& lines, float maxWidth);

   };

}

