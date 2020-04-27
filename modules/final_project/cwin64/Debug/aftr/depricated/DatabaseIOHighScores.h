#pragma once

#include <string>
#include <vector>
#include <map>

namespace Aftr
{

class DatabaseIOHighScores
{
	public:

	/**
	 * Default constructor: initializes default values.
	 */
	DatabaseIOHighScores();

   virtual ~DatabaseIOHighScores();

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
	 * Assign the sandbox with which we will interact
	 */
	virtual bool setSandbox( const std::string& newSandbox );

	/**
	 * Retrieve the name of the currently-in-use sandbox
	 */
   virtual std::string getSandbox();

	/* ***********************************************************
		Functions for SENDING
	*********************************************************** */

	/**
	 * Assigns the name of the score line to send
	 */
	virtual bool setName( const std::string& newName );

	/**
	 * Assigns the score of the score line to send
	 */
	virtual bool setScore( long newScore );

	/**
	 * Send the scores to the server and wait for the return.
	 * @return true if the scores were successfully sent, false otherwise.
	 */
	virtual bool sendScores();

	/* ***********************************************************
		Functions for RECEIVING
	*********************************************************** */

	/**
	 * Sets the maximum number of scores that we wish to have returned to us.
	 * You will receive at most this many scores in return.
	 * Scores are sorted by descending score.
	 * If unset, will effectively mean "no limit" to number of returned scores
	 */
	virtual bool setMaxScoreReturnCount( int newScoreCount );

	/**
	 * Sets the cutoff time past which scores are "obsolete" and considered
	 * to not exist.  Useful if you only want "today's" high scores or similar.
	 * Set in UNIX time.  If left unset, will not consider time when returning results
	 */
	virtual bool setScoreCutoffTime( int newScoreCutoffTime );

	/**
	 * Issue the query and retrieve the scores from the server
	 */
	virtual bool receiveScores();

	/**
	 * Get the number of results that we have
	 */
	virtual int getResultCount();

	/**
	 * Get the name at a certain row
	 */
	std::string getName( int row );

	/**
	 * Get the score at a certain row
	 */
	virtual long getScore( int row );

	/**
	 * Get the timestamp at a certain row
	 */
	virtual std::string getTimestamp( int row );

	/**
	 * Get the IP address at a certain row
	 */
	virtual std::string getIPAddress( int row );

	protected:

	std::string theSandbox;		// The sandbox to which to connect
	std::string baseURL;			// Base domain for connection (server to which we connect)
	int thePort;			// The port we connect on (probably 80 for HTTP)
	int socketDescriptor;		// The socket descriptor connection to the server (in and out)
   long timeOutValueInSeconds; ///< Time, in seconds, this instance waits after attempting to contact remote host before failing.

	/* ***********************************************************
		Variables for SENDING
	*********************************************************** */

	std::string saveURL;			// URL to which we SEND results
	std::string theName;			// The name to send to the server
	long theScore;			// The score to send to the server

	/* ***********************************************************
		Variables for RETRIEVING
	*********************************************************** */
	
	std::string getURL;			// URL from which we OBTAIN results
	int theScoreCount;		// Maximum number of scores that we wish to receive back
	int theScoreCutoffTime;		// Cutoff time past which scores are considered 'obsolete'
	int resultCount;		// Number of results that we have obtained
   std::vector< std::map< std::string,std::string > > storedResults;	// Each vector row holds a map, which is the entry links

};
} //namespace Aftr

