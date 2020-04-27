#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include <string>
#include "guichan/imagefont.hpp"
#include "guichan/graphics.hpp"
#include <cmath>




namespace gcn
{
    class Color;
    class Graphics;
    class Image;

    /**
     * A font using an image containing the font data. It implements the font
     * class. You can use any filetype for the font data as long as it can be
     * loaded with your ImageLoader.
     *
     * This are two examples of an image containing a font.
     *  \image html imagefontexample.bmp
     *  \image html imagefontexample2.bmp
     *
     * The Image font format works like this: The first pixel, the pixal at
     * coordinate (0,0), tells which color to look for when seperating glyphs.
     * You create an image with your glyphs and simple separates them with
     * the seperation color. When you create your ImageFont you supply the
     * constructor with the glyphs present in your image. When creating an
     * ImageFont for the image data in the first example above, the following
     * constructor call would be used.
     * @code gcn::ImageFont imageFont("fixedfont_big.bmp"," abcdefghijklmno\
pqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"); @endcode
     * Noteworthy is that the first glyph actually gives the width of space.
     * Glyphs can, as seen in the second example above, be seperated with
     * horizontal lines making it possible to draw glyphs on more then one
     * line in the image. However, these vertical lines must be of one pixel
     * size!
     */
class GCN_CORE_DECLSPEC GUIFontResizable: public ImageFont
{

public:

   /**
   * Constructor which takes an image file containing the font and
   * a string containing the glyphs. The glyphs in the string should
   * be in the same order as they appear in the font image.
   *
   * @param filename the filename of the image.
   * @param glyphs the glyphs found in the image.
   * @param the size of the font, default is one and it takes what ever the size of the font is
   * @throws Exception when glyph list is incorrect or the font file is
   *                   corrupt or if no ImageLoader exists.
   */
   GUIFontResizable(const std::string& filename, const std::string& glyphs, float size = 1);

   /**
   * Constructor which takes an image file containing the font and
   * two boundaries of ASCII values. The font image should include
   * all glyphs specified with the boundaries in increasing ASCII
   * order. The boundaries are inclusive.
   *
   * @param filename the filename of the image.
   * @param glyphsFrom the ASCII value of the first glyph found in the
   *                   image.
   * @param glyphsTo the ASCII value of the last glyph found in the
   *                 image.
   * @param size the size of the font, default is 1
   * @throws Exception when glyph bondaries are incorrect or the font
   *                   file is corrupt or if no ImageLoader exists.
   */
   GUIFontResizable(const std::string& filename, unsigned char glyphsFrom=32,
      unsigned char glyphsTo=126, float size = 1);

   /**
   * Destructor.
   */
   virtual ~GUIFontResizable();

   /**
   * Draws a glyph.
   *
   * NOTE: You normally won't use this function to draw text since
   *       the Graphics class contains better functions for drawing
   *       text.
   *
   * @param graphics a graphics object to be used for drawing.
   * @param glyph a glyph to draw.
   * @param x the x coordinate where to draw the glyph.
   * @param y the y coordinate where to draw the glyph.
   * @return the width of the glyph in pixels.
   * @see Graphics
   */
   virtual int drawGlyph(Graphics* graphics, unsigned char glyph,
      int x, int y);


protected:

   /**the size of the font to draw with*/
   float fontSize;
};

} //namespace gcn

#endif //STM_CONFIG_USE_GUICHAN
