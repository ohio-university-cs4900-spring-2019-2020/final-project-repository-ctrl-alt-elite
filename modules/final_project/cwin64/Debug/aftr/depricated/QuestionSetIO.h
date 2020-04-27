//Created by Bruce Bilyeu from Jim Wylie's original HighestScore.h 
//and reference to microsoft developer's network

//Rewritten by Scott Nykl to remove all references to ANY platform dependent
//socket technology. In its place, I have created a AftrTCPSocket that
//deals uses an open source package capable of running cross-platform

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

namespace Aftr 
{

class QuestionSetIO
{
public:
   /**
      Default constructor: initializes default values.
   */
   QuestionSetIO();

   /**
      Default destructor
   */
   virtual ~QuestionSetIO();

	/**
	   Assign the DatabaseIOQuestions with which we will interact
	*/
	virtual bool setQuestionSet( const std::string& newQuestionSet );

	/**
	   Retrieve the name of the currently-in-use question set
	*/
	virtual std::string getQuestionSet();

   /* ***********************************************************
		Functions for SENDING question results
	*********************************************************** */

   /**
	 * Send the results to the server and wait for the return.
	 * @return true if the results were successfully sent, false otherwise.
	 */
	virtual bool sendResult( const std::string& studentID, const std::string& questionID, const std::string& answerID, int responseTime = 0 );

	/* ***********************************************************
		Functions for RECEIVING question set
	*********************************************************** */

	/**
	 * Issue the query and retrieve the questions from the server
	 */
	virtual bool receiveQuestions();

	/* ***********************************************************
		Functions for accessing data
	*********************************************************** */

	/**
	 * Get the number of questions that we have
	 */
	virtual int getResultCount();

	/**
	 * Get the number of choices that we have at a certain row
	 */
	virtual int getNumberChoices( int row );

   /**
	 * Get the question id at a certain row
	 */
   virtual std::string getQuestionID( int row );

   /**
	 * Get the question at a certain row
	 */
	virtual std::string getQuestion( int row );

   /**
	 * Get the advanced tag at a certain row
	 */
   virtual std::string getAdvancedTag( int row );

   /**
	 * Get the audio file location at a certain row
	 */
   virtual std::string getAudio( int row );

   /**
	 * Get the diagram file location at a certain row
	 */
   virtual std::string getDiagram( int row );

   /**
	 * Get the answer id at a certain row
	 */
   virtual std::string getAnswerID( int row );

   /**
	 * Get the choice id at a certain row for a certain choice number
	 */
   virtual std::string getChoiceID( int row, int choicenum );

   /**
	 * Get the choice at a certain row for a certain choice number
	 */
   virtual std::string getChoice( int row, int choicenum );

   /**
	 * Get the choice id at a certain row for a certain choice
	 */
   virtual std::string getChoiceID( int row, std::string choice );

protected:

   //Universal variables
   std::string theQuestionSet;  // The question set to which to connect to and use
   int resultCount;		   // Number of questions that we have obtained(size of vectors)
   std::vector<std::map<std::string,std::string> > storedResults;	// Each std::vector row holds a std::map, which is the entry links
   std::vector<int> numChoices; // Stores the number of choices for each question
};


} //namespace Aftr

