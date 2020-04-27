//Created by Bruce Bilyeu from Jim Wylie's original HighestScore.h 
//and reference to microsoft developer's network

//Rewritten by Scott Nykl to remove all references to ANY platform dependent
//socket technology. In its place, I have created a AftrTCPSocket that
//deals uses an open source package capable of running cross-platform


#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

namespace Aftr 
{

class DatabaseIOQuestions
{
public:
   /**
      Default constructor: initializes default values.
   */
   DatabaseIOQuestions();

   /**
      Default destructor
   */
   virtual ~DatabaseIOQuestions();

   /**
      Specifies how long this instance will wait to contact remote server before giving up.
      This timeout value is used by all methods that attempt to send or recieve data remotely.
      This value can be changed at any time. After changing, all subsequently invokations of
      methods that contact remote endpoints will use this new timeout value.
   */
   virtual void setConnectionTimeOutValue( long timeOutInSeconds );

   /**
      \returns The time, in seconds, this instance will wait after attempting to contact
      a remote host before returning failure status.
   */
   virtual long getConnectionTimeOutValue();

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
   virtual std::string DatabaseIOQuestions::getAnswerID( int row );

   /**
	 * Get the choice id at a certain row for a certain choice number
	 */
   virtual std::string DatabaseIOQuestions::getChoiceID( int row, int choicenum );

   /**
	 * Get the choice at a certain row for a certain choice number
	 */
   virtual std::string DatabaseIOQuestions::getChoice( int row, int choicenum );

   /**
	 * Get the choice id at a certain row for a certain choice
	 */
   virtual std::string DatabaseIOQuestions::getChoiceID( int row, std::string choice );

protected:

   //Universal variables
   std::string theQuestionSet;  // The question set to which to connect to and use
   std::string baseURL;			// Base domain for connection (server to which we connect)
   std::string audioBaseURL;    // Base URL for the audio location
   std::string diagramBaseURL;  // Base URL for the diagram location
   char thePort;			   // The port we connect on (probably 80 for HTTP)
   long timeOutValueInSeconds; ///< Time, in seconds, this instance waits after attempting to contact remote host before failing.

   /* ***********************************************************
   Variables for SENDING
   *********************************************************** */

   std::string saveURL;			// URL to which we SEND results

   /* ***********************************************************
   Variables for RETRIEVING
   *********************************************************** */

   std::string getURL;			   // URL from which we OBTAIN question set
   int resultCount;		   // Number of questions that we have obtained(size of vectors)
   std::vector<std::map<std::string,std::string> > storedResults;	// Each std::vector row holds a std::map, which is the entry links
   std::vector<int> numChoices; // Stores the number of choices for each question
};

} //namespace Aftr
