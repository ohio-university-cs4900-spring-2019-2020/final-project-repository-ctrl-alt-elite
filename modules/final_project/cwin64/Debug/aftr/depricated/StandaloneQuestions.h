//Stand-alone Question Set Class
//Coded by Mike Farrell
//based on base class from Aftr Engine

//this class is intended for use with *.sqs files
//outputted from the Steam Question Set Editor applet

#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include "QuestionSetIO.h"

namespace Aftr
{

class StandaloneQuestions : public QuestionSetIO
{
  public:

     /**
        Reads the standard sqs directory and returns possible sqs files
     */
     static std::vector<std::string> getAvailableSets();

     /**
        Default constructor: initializes default values.
     */
     StandaloneQuestions();

     /**
        Default destructor
     */
     ~StandaloneQuestions();


     //not pertinent to standalone
     virtual void setConnectionTimeOutValue(long timeOutInSeconds);
     virtual long getConnectionTimeOutValue();

	   /**
	      this is now the name of the file (within the standard question set path)
	   */
	   bool setQuestionSet( const std::string& filename);
 
 	   /**
	     Retrieve the name of the currently-in-use question set
	   */
	   std::string getQuestionSet();


     //does nothing, emulation routine
      bool sendResult( const std::string& studentID, const std::string& questionID, const std::string& answerID, int responseTime = 0 );


     //parses questions from disk, returns false on failure
	   bool receiveQuestions();



	   /* ***********************************************************
		   Functions for accessing data
	   *********************************************************** */

	   /**
	    * Get the number of questions that we have
	    */
	   int getResultCount();

	   /**
	    * Get the number of choices that we have at a certain row
	    */
	   int getNumberChoices(int row);

     /**
	   * Get the question id at a certain row
	   */
     std::string getQuestionID(int row);

     /**
	   * Get the question at a certain row
	   */
	   std::string getQuestion(int row);

     /**
	   * Get the advanced tag at a certain row
	   */
     std::string getAdvancedTag(int row);

     /**
	   * Get the audio file location at a certain row
	   */
     std::string getAudio(int row);

     /**
	   * Get the diagram file location at a certain row
	   */
     std::string getDiagram(int row);

     /**
	   * Get the answer id at a certain row
	   */
     std::string getAnswerID(int row);

     /**
	   * Get the choice id at a certain row for a certain choice number
	   */
     std::string getChoiceID(int row, int choicenum);

     /**
	   * Get the choice at a certain row for a certain choice number
	   */
     std::string getChoice(int row, int choicenum);

     /**
	   * Get the choice id at a certain row for a certain choice
	   */
     std::string getChoiceID(int row, std::string choice);

     /**
     * Get the feedback string for wrong answer for given question
     */
     std::string getFeedback(int row, bool wrap);


     //internal exceptions...
     class exParseError : public std::exception {};

   private:

     std::string filename;
      
     //internal storage record for question's in a set
     struct Question
     {
       std::string question, feedback;
       std::vector<std::string> answers;
       int correct_ans;
     };

     std::vector<Question> questions;

     //utility methods...
     bool parse_sqs_file(const std::string &fn);

};


} //namespace Aftr
