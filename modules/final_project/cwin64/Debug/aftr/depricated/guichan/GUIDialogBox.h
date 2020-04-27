/// This is the widget will be showing the status of the character's Wood. 
/// The wood is designed to show progress of the character at building his next boat.
/// The wood meter will show on screen the status of the Wood.
#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include "GUIBox.h"
#include <vector>

struct Mix_Chunk;

namespace gcn
{
   class ImageFont;
   class Button;
   class TextBox;
   class ScrollArea;
}

namespace Steamie
{

class GLView;
class GUI;


class GUIDialogBox : public GUIBox
{
public:
   friend class GUIDialogButton;
   GUIDialogBox( gcn::ImageFont* font, std::string caption, std::vector< std::string >& text, 
                 std::vector< std::string >& audioFiles, GLView* glView );

   ///Destructor, handles any memory clean up
   virtual ~GUIDialogBox();

   void setDialogBoxHeight( int y ) { this->dbHeight = y; }
   void setDialogBoxWidth( int x ) { this->dbWidth = x; }
   int getDialogBoxHeight();
   int getDialogBoxWidth();

   /**
      stops the sound currently playing
      */
   void stopSound(); 
   ///The overloaded draw function
   //void draw(gcn::Graphics* graphics);

   void mutesound() { mute = true; }
   void unmutesound() { mute = false; }

   virtual void clickFocusedWidget();

protected:

   int dbHeight;
   int dbWidth;

   virtual void displayCurrentIndex();
   
   std::string caption;
   std::vector< std::string > text;

   #ifdef STM_CONFIG_USE_SDL_MIXER
      std::vector< Mix_Chunk* > audio;
   #endif

   std::vector< int > audioIndiciesAlreadyPlayed;

   /**the index of the previously displayed index*/
   int prevIndex;


   gcn::TextBox* textBox;
   gcn::ScrollArea* scrollArea;
   gcn::Button* butClose;
   gcn::Button* butNext;
   gcn::Button* butBack;
   gcn::Button* replaySoundBtn;

   gcn::ImageFont* symbols;

   int soundchannel;

   static bool mute;
   
   //the base glView 
   GLView* glView;
};


} //namespace Steamie

#endif //STM_CONFIG_USE_GUICHAN
