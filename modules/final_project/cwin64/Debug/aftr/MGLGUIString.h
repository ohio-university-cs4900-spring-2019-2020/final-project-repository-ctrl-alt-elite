#pragma once

#include "MGLGUI.h"
#include "Font.h"
#include "AftrGlobals.h"
#include <string>

namespace Aftr
{

   class MGLGUIString : public MGLGUI
   {
   public:
      static MGLGUIString* New( WO* parent, const std::string& label );
      virtual ~MGLGUIString();
      virtual void render( const Camera& cam );
      void setLabel( const std::string& label );
      void setColor( aftrColor4ub color ) { this->color = color; }
      void setColor( GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);
      float getWidthAbs();
      float getHeightAbs();

      void setFont( const std::string& fontPath );
      void setSize( size_t fontSize );
      void setFontOrientation( FONT_ORIENTATION orientation );
      void setFontJustification( FONT_JUSTIFICATION justification );
      void setFontEmboldeningCoefficient( float x );

      virtual void updateStencilBoundingQuad( bool stencilOpINCorDEC, GLubyte red = 255, GLubyte green = 255, GLubyte blue = 255 );
      void updateHeightAndWidthOfLabel();

      Font* getFont() { return font; }

      std::string& getLabel() { return label; }

      virtual void isUsingStencilBuffer( bool useStencilBufferForClipping );
      
   protected:
      MGLGUIString( WO* parent, const std::string& label );
      virtual void onCreate();
      Font* font;
      std::string label;
      Aftr::aftrColor4ub color;
      float width;
      float height;
      FONT_ORIENTATION fontOrientation;
      FONT_JUSTIFICATION fontJustification;
   };

}

