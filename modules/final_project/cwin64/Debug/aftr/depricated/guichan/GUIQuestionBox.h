#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include "GUIBox.h"

#include <string> 

namespace gcn
{
   class ImageFont;
   class Button;
   class TextBox;
   class ScrollArea;
   class RadioButton;
}

#include "guichan/actionlistener.hpp"

namespace Steamie
{

   class GLView;

 /**
    \class GUIQuestionBox
    \Author Bruce Bilyeu - Ported and Updated by Mitchell Leitch
    \brief A multiple choice question box for GUIs
    This is a multiple choice question box for the GUI. It can take any number of possible choice answers barring 
    your available window space. To create one, pass these parameters into the constructor (in order):
      # font - the font you want to use for the question
      # caption - the text at the top of the window i.e. Question 1
      # text - the actual question
      # choices - a vector of strings, these are the multiple choice answers
      # audioFile - a string, the audio file that plays when show() is called. If you pass in "" (empty string), there will be no sound
    This can be easily a true or false question as well, just make sure choices is filled only with true and false =).
    There are a couple ways to use this box and to get whether the user's answer was correct or incorrect:
      * You can keep a vector of question boxes and check them by using isCorrect() it returns a bool
      * The question box generates an event when "Answer it" button is clicked. You can act differently per question this way.
        You can compare the widget passed into action against your action, then you can check if the question was answered correctly,
        by either checking the bool isCorrect or the eventId is set to 'correct' or 'incorrect'.
    \{
    */
class GUIQuestionBox : public GUIBox, public gcn::ActionListener
{
public:
   friend class GUIQuestionButton;
   GUIQuestionBox( gcn::ImageFont* font, std::string caption, std::string text, 
                 std::vector< std::string >* choices, std::string audioFile, unsigned int correctIndex = -1, GLView* view = NULL);

   /**overloaded action listener so the question box can listen for its own widgets to act on button and mouse presses*/
   virtual void action(const std::string& eventId, gcn::Widget* widget);

   ///Destructor, handles any memory clean up
   ~GUIQuestionBox();

   /**toggles showing the question box*/
   void show();
   /**Always hides the question box*/
   void hide();

   /**sets to autohide the question box after a user clicks answer it*/
   void setAutoHide( bool hide ) { autoHide = true; }
   /**gets whether the question box will auto hide*/
   bool getAutoHide() { return autoHide; }

   /**true if the user answered the question correctly*/
   bool isCorrect( ) { return correct; }

   std::string userChoice() { return answerChoose; }
   std::vector< std::string >* getChoices() { return this->choices; }
   std::string getQuestionText() { return text; }
   std::string getCorrectAnswerText() { return correctAnswer; };

   /**
      simulates a click of a widget button on a question box, allows for highlighting of selected answers
      if the answer button is clicked and no radio buttons are highlighted it will just ignore until 
      one answer is selected
      */
   virtual void clickFocusedWidget();

   /**
      focuses the answer button so when a new qbox pops up it will have the focus
      */
   void focusAnswerBtn();
protected:
   /**Adjusts the width of the text to make sure new lines are in the proper location and all the text is readable*/
   void adjustTextWidth(std::string & textToEdit, int desiredLen);
   /**Inits the questions and the multiple choice answer radio buttons based on the question*/
   void initQuestionBox();

   gcn::Font* font;

   /**The caption of the text box (ie question 2)*/
   std::string caption;
   /**The actual question text*/
   std::string text;

   #ifdef STM_CONFIG_USE_SDL_MIXER
      /**The audio file accompanying the question*/
      Mix_Chunk* audio;
   #endif

   /**The strings of the multiple choice responses*/
   std::vector< std::string >* choices;
   /**stores the correct answer to the question*/
   std::string correctAnswer;

   gcn::ScrollArea* scrollArea;

   /**The text box with the question inside of it*/
   gcn::TextBox* questionTBox;
   
   /**The button the user needs to press to answer the question*/
   gcn::Button* answerBtn;

   /**The radio buttons for the multiple choice options*/
   std::vector< gcn::RadioButton* >* rdoAnswers;

   std::vector< gcn::TextBox* >* tbAnswers;

   /**the answer to the multiple choice question*/
   std::string answerChoose;
   int choiceIndex;

   /**the correct answer to the multiple choice question*/
   //std::string correctAnswer;
   int correctIndex;

   /**true if the user selected the correct radio button response to the question*/
   bool correct;

   /**true, the question box will autohide when the user clicks "Answer It!".
      default value is false*/
   bool autoHide; 
};

/** \} */
} //namespace Steamie

#endif //STM_CONFIG_USE_GUICHAN
