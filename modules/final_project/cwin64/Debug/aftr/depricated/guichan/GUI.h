#pragma once
#ifdef STM_CONFIG_USE_GUICHAN

//#include "Predefined.h"
#include "guichan.hpp"  //GUI inherits from a GUIChan ActionListener
#include "guichan/sdl.hpp" //GUIChan makes use of SDL
#include "guichan/opengl.hpp" //GUIChan uses platform's opengl
#include "guichan/opengl/openglsdlimageloader.hpp" //GUIChan has its own image loader
#include "QuestionSetIO.h"

namespace Steamie
{
   class WO;
   class DatabaseIOQuestions;
   class GUIQuestionBox;

class GUI : public gcn::ActionListener
{
public:
   //GUI( GLView* view ); //Abstract Class!!!
   virtual ~GUI();
   virtual void render() = 0;
   virtual void action( const std::string& action, gcn::Widget* widget ) = 0;
   virtual bool handleEvent( SDL_Event new_event ) = 0;

   /**Overloadable, update function that can be called for objects that aren't guichan, but interact with the GUI.
      interactingWO is the WO that is doing the interaction (might need for more information later*/
   virtual void update( WO* interactingWO = NULL ) {};

   /**Shows the gui if it has been hidden*/
   virtual void show();

   /**Hides the gui if it is visible*/
   virtual void hide();

   gcn::Container* getTop() { return top; }

   GLView* getGLView() { return this->view; }
 
   /**
      Initializes and returns a vector of question boxes from the database with the name 'setName', and initializes the dbQuestionSet
      \param setName - the name of the question set from the database
      \param dbQuestionSet - the database IO for the question set, the user must allocate this or the function will not work
                             the user does not need to keep track of this if they are just interested in the questions.
      \returns vector<GUIQuestionBox*>* - the question set that was created from the input parameters. This returns a pointer
                                          the user must do the manual clean up of the question boxes and vectors
   */
   virtual std::vector< GUIQuestionBox* >* initAQuestionSet( std::string setName, QuestionSetIO* dbQuestionSet, gcn::ImageFont* font ); 
   virtual void initAQuestionSet( std::vector< GUIQuestionBox* >* );

protected:
   void setCaption( std::string caption );
   
   #ifdef STM_CONFIG_USE_SDL_MIXER
      virtual void initSound( int frequency = 22050, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunkSize = 1024 );
   #else
      virtual void initSound( int frequency = 22050, Uint16 format = 0x800, int channels = 2, int chunkSize = 1024 ); ///< Stub method since MIX_DEFAULT_FORMAT is declared in non-existant MIXER lib
   #endif
   
   void initKeyboard( int enableUnicode = 1, int delay = SDL_DEFAULT_REPEAT_DELAY, int interval = SDL_DEFAULT_REPEAT_INTERVAL );

   virtual void init( GLView* view );
   virtual void initWidgets() = 0;

   gcn::Gui* gui;            // A Gui object - binds it all together
   gcn::Container* top;      // A top container
   
   /**
      All instantiated widgets used by this GUI. The user should push any
      widgets created inside of GUINewModule::initWidgets() into this list.
      Allows user to iterate through all widgets.
   */
   std::vector< gcn::Widget* > widgets;
   
   GLView* view;

   /**
      SDL Stuff we need
   */
   SDL_Event guiEvent;
};

} //namespace Steamie

#endif //STM_CONFIG_USE_GUICHAN
