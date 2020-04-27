#pragma once
#include <iostream>

/*************************************************************************
 Written by Scott Nykl. enum class representing layouts for the GL 
 Fonts used in the engine.
*************************************************************************/
namespace Aftr
{
   //orientations for fonts
   enum class FONT_ORIENTATION : unsigned char { foCENTER = 0, foLEFT, foRIGHT, foTOP, foBOTTOM, foLEFT_TOP, foRIGHT_TOP, foLEFT_BOTTOM, foRIGHT_BOTTOM };
   std::ostream& operator<<( std::ostream& out, const FONT_ORIENTATION& fo );

   enum class FONT_JUSTIFICATION : unsigned char { fjCENTER = 0, fjLEFT, fjRIGHT, fjFULL };
   std::ostream& operator<<( std::ostream& out, const FONT_JUSTIFICATION& fj );

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
   enum class FONT_ASPECT_RATIO_TYPE : unsigned char { FIXED_BY_WIDTH, FIXED_BY_HEIGHT, FIXED_BY_WIDTH_AND_HEIGHT };
   std::ostream& operator<<( std::ostream& out, const FONT_ASPECT_RATIO_TYPE& art );
}
