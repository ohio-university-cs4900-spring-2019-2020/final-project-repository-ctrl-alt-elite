#pragma once

#include "SteamieConfig.h"
#ifdef STM_CONFIG_USE_GUICHAN

#include "GUIDialogBox.h"
#include "guichan/widgets/icon.hpp"

namespace Steamie
{

/**
   \class GUIPictureTextBox
   \author Mitchell Leitch
   This is a text box with a picture that can be located in respect to the text in
   any direction (up, down, left, right). There will be a option to add additional 
   slides so can do multiple text boxes in one. Inherits from GUIDialog box.
   \{
   */

enum PictureLocation { UP = 0, DOWN, LEFT, RIGHT };

class GUIPictureTextBox : public GUIDialogBox
{
public:
   
   GUIPictureTextBox( gcn::ImageFont* font, std::string caption, std::vector< std::string >& text, 
      std::vector< std::string >& audioFiles, GLView* glView, std::vector< std::string >* texturePaths );

   virtual ~GUIPictureTextBox();

   virtual void draw(gcn::Graphics* graphics);



protected:

   /**Overloaded, to display current picture and associated text*/
   virtual void displayCurrentIndex();

   std::vector< gcn::Icon* > images;

};



} //  namespace Steamie

#endif //STM_CONFIG_USE_GUICHAN
