#pragma once

#include "MGL.h"

namespace Aftr
{
   class Font; 

   class MGLString : public MGL
   {
   public:
      static MGLString* New(WO* parent, std::string str, std::string fontPath, size_t fontSize, float worldSpaceHeight);
      virtual ~MGLString();
      virtual void render( const Camera& cam );
      void setColor( Aftr::aftrColor4ub color ) { this->color = color; }
      Font* getFont();
      /// Returns the text that this MGLString renders.
      std::string getText() { return this->str; }
   protected:
      MGLString(WO* parent, std::string str, std::string fontPath, size_t fontSize, float worldSpaceHeight);
      virtual void onCreate();
      std::string str;
      Font* myFont = nullptr;
      Aftr::aftrColor4ub color;
      float height;
      Vector oldSize;//size on previous render, if it changed update the bounding box
   };
}

