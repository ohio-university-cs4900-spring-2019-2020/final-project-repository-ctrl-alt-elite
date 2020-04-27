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
#include "FontAlignments.h"

namespace Aftr
{
   class FontDataShared;
   class AftrFrameBufferObject;
   class GLSLShader;
   class GLSLUniform;

   class Font
   {
   public:
      Font( FontDataShared* fontDataShared );
      virtual ~Font();
               
      //shouldn't need overridden in inherited classes
      float getWidthOfString( const std::string& str );
      float getHeightOfString( const std::string& str );
      FontDataShared* getDataShared() { return dataShared; }
      void render(const std::string& str, const Mat4& modelMatrix, const Camera& cam, FONT_ORIENTATION orientation = FONT_ORIENTATION::foCENTER, bool useCache = true, QuadOrientation qo = QuadOrientation::qoXY, FONT_JUSTIFICATION justification = FONT_JUSTIFICATION::fjCENTER)
      {
         print(str, modelMatrix, cam, orientation, useCache, qo, justification);
      }
      bool isUsingFragDepth() { return this->UseFragDepth; }
      void isUsingFragDepth(bool useFragDepthInFragmentShader);
      /// Returns the fragment depth assigned to each fragment of this font
      float getFragDepth() { return this->FragDepth; }
      void setFragDepth(float fragmentShaderDepthPerFragment);
      /**
      When set to true, this widget is stenciled (clipped) by parents bounding volume.
      This is true by default. To opt out of using the stencil buffer, set this to false.
      */
      virtual void isUsingStencilBuffer(bool useStencilBufferForClipping);
      virtual bool isUsingStencilBuffer() { return this->IsUsingStencilBuffer; }
      //the expected output of print is a quad of size getWidth by getHeight in whatever coordinate system you are using
      void print(const std::string& str, const Mat4& modelMatrix, const Camera& cam, FONT_ORIENTATION orientation = FONT_ORIENTATION::foCENTER, bool useCache = true, QuadOrientation qo = QuadOrientation::qoXY, FONT_JUSTIFICATION justification = FONT_JUSTIFICATION::fjCENTER);

      //should need overridden in inherited classes
      //virtual void adjustForWidthJustification(const std::string& label, float maxWidth, FONT_JUSTIFICATION justification) = 0;
      virtual void adjustForWidthOrientation(const std::string& label, FONT_ORIENTATION orientation, Mat4& modelMatrix) = 0;//adjusts the render position for the orientation using glTranslatef(), width orientation should be called on each line seperately
      virtual void adjustForHeightOrientation(const std::string& label, FONT_ORIENTATION orientation, Mat4& modelMatrix) = 0;//adjusts the render position for the orientation using glTranslatef(), height orientation should be called on blocks of text together
      
   protected:
      Font() = delete;
      FontDataShared* dataShared = nullptr;
     // void printCachedString( const std::string& str, const Camera& cam, FONT_ORIENTATION orientation, QuadOrientation qo );
     // void printUncachedString( const std::string& str, const Camera& cam, FONT_ORIENTATION orientation, FONT_JUSTIFICATION justification = FONT_JUSTIFICATION::fjCENTER, float madWidth = 0 );
     // void cacheString( const std::string& str, const Camera& cam, FONT_ORIENTATION orientation );
      
      AftrFrameBufferObject* fbo;
      GLSLShader* shader;
      GLSLUniform* useFragDepth; bool UseFragDepth;
      GLSLUniform* fragDepth; float FragDepth;
      bool IsUsingStencilBuffer; ///< True by default. When true, this widget is stenciled (clipped) by parents bounding volume
      
      virtual void print(const std::string& str, const Mat4& modelMatrix, const Camera& cam, FONT_ORIENTATION orientation, bool useCache, Aftr::QuadOrientation qo, FONT_JUSTIFICATION justifcation, const std::vector< std::string >& lines, float maxWidth) = 0;
      virtual void renderCharacter(unsigned char charcode, Mat4& modelMatrix, const Camera& cam ) = 0;///< renders an individual character
      
   };

}

