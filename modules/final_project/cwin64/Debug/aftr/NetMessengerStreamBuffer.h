#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include <string>

namespace Aftr
{

class NetMessengerStreamBuffer
{
public:
   /**
      Default constructor creates a dynamically resizable buffer that can perform either insertion 
      or extraction operations. Do not mix insertion with extraction operations. Use the stream as
      either insertion only or extraction only. Call getBuffer() to get access to the internal
      contiguous array. The user MUST EXPLICITLY FREE this buffer's internal buffer since it is expected
      that this stream is meant as an intermediary to convert to/from net stream data.
   */
   NetMessengerStreamBuffer( bool deleteInternalBufferOnDestruction = false, unsigned int initialCapacityBytes = DEFAULT_BUF_SIZE );

   /**
      This constructor sets the internal buffer and buffer length to the in passed values.
      The user MUST EXPLICITLY FREE this buffer's internal buffer since it is expected
      that this stream is meant as an intermediary to convert to/from net stream data.
   */
   NetMessengerStreamBuffer( char* bufPtr, unsigned int maxBufLenInBytes, bool deleteInternalBufferOnDestruction = false );
   NetMessengerStreamBuffer( NetMessengerStreamBuffer&& toMove ) noexcept;
   ~NetMessengerStreamBuffer();

   NetMessengerStreamBuffer& operator=( const NetMessengerStreamBuffer& toAssign ) = delete;
   NetMessengerStreamBuffer( const NetMessengerStreamBuffer& toCopy ) = delete;
   NetMessengerStreamBuffer& operator=( NetMessengerStreamBuffer&& toMoveAssign ) = default;

   /// Extraction operators (exiting the stream)
   NetMessengerStreamBuffer& operator>> ( unsigned int& val );
   NetMessengerStreamBuffer& operator>> ( int& val );
   NetMessengerStreamBuffer& operator>> ( unsigned short& val );
   NetMessengerStreamBuffer& operator>> ( float& val );
   NetMessengerStreamBuffer& operator>> ( double& val );
   NetMessengerStreamBuffer& operator>> ( std::string& s );
   NetMessengerStreamBuffer& operator>> ( unsigned char& c ); ///< Binary data (bytes)
   NetMessengerStreamBuffer& extractBytes( uint8_t* data, unsigned int lenBytes ); ///< Insert a block of Binary data (bytes)
   

   /// Insertion operators (entering the stream)
   NetMessengerStreamBuffer& operator<< ( unsigned int val );
   NetMessengerStreamBuffer& operator<< ( int val );
   NetMessengerStreamBuffer& operator<< ( unsigned short val );
   NetMessengerStreamBuffer& operator<< ( float val );
   NetMessengerStreamBuffer& operator<< ( double val );
   NetMessengerStreamBuffer& operator<< ( char* cString );
   NetMessengerStreamBuffer& operator<< ( const std::string& s );
   NetMessengerStreamBuffer& operator<< ( unsigned char c ); ///< Binary data (bytes)
   NetMessengerStreamBuffer& insertBytes ( uint8_t* data, unsigned int lenBytes ); ///< Insert a block of Binary data (bytes)

   std::string toString() const;

   /**
      If the default constructor was used to create this stream's own internal buffer which is dynamically
      resizable, this method deletes the internal buffer freeing the memory.The user MUST EXPLICITLY FREE
      this buffer's internal buffer since it is expected that this stream is meant as an 
      intermediary to convert to/from net stream data. 

      If this instance was creating by passing in an external buffer, this method will also free that 
      memory as well.

      After this method is invoked, the stream is invalidated and should no longer be used without proper
      reinitialization.
   */
   void freeInternalBufferNow();
   
   /// Returns a pointer to the beginning of this stream's contiguous internal buffer.
   /// This pointer may change after a dynamic resize of the internal buffer, so call this method
   /// after all necessary operations have been performed to ensure this value will no longer change.
   char* getBuffer() { return this->bufPtr; }

   /// Returns the size, in bytes, from start of buffer to the current position in the stream
   unsigned int getBufferLen() const { return this->currBufLen; }

   /// Returns the size, in bytes, of this stream's contiguous internal buffer
   unsigned int getBufferSizeBytes() const { return this->bufLen; }

   /// Returns a pointer to the current byte at which the read/write pointer internal to the contiguous buffer is pointing
   char* getCurrentBufferLocation() { return this->currPos; }
   size_t getCurrentOffsetLocation() { return this->currPos - this->bufPtr; }

   /// Jumps the internal read/write pointer to 'x' bytes beyond the first byte of the internal contiguous buffer
   void seekToOffset( unsigned int offsetInBytes ) { this->currPos = this->bufPtr; this->currPos += offsetInBytes; }

   /// Jumps the internal read/write pointer to the byte directly after the last written byte
   void seekToEnd() { this->currPos = this->bufPtr; this->currPos += this->currBufLen; }

   /// Jumps the internal read/write pointer to the first byte of this stream's contiguous internal buffer
   void seekToBeginning() { this->currPos = this->bufPtr; }

   /// This method overwrites the currently computed internal current buffer length with the
   /// in passed value. This is useful when the user may want to jump to a random byte within
   /// the stream, perform an insertion / extraction operation (which implicitly adds to / subtracts
   /// from the internally stored current buffer length) and then increment / decrement by the size
   /// of the data type which was inserted / extracted.
   void  overwriteBufferLen( unsigned int newBufferLen ) { this->currBufLen = newBufferLen; }

   /// This method recomputes and updates the second 4 bytes of the header to the size, in bytes,
   /// of the payload within this stream. This method is useful when creating NetMsgGeneric,
   /// and the user manually inserts values into the stream outside of the NetMsg's toStream
   /// method.
   void updatePayloadLengthInHeader();

   /// Set to true when an extraction operation reads beyond the end of the buffer and is therefore unsuccessful.
   /// This flag remains set until clearFlags() is called.
   bool extractedAllData() { return this->reachedEndOfData; }

   /// Set to true when an insertion operation is unable to write value because the buffer is full, but
   /// this instance cannot resize the corresponding buffer because this stream instance is not set to
   /// be the owner of the buffer and therefore cannot resize to resolve the issue.
   bool bufferOverflowed() { return this->filledBufferNotOwnedByThisStream; }

   /// Resets flags that are set when extraction beyond end of buffer occurs or insertion
   /// beyond buffer size and no ability to resize the buffer because it is not owned.
   bool clearFlags() 
   {
      this->reachedEndOfData = false;
      this->filledBufferNotOwnedByThisStream = false;
      return true;
   }

   bool isGood()
   {
      if( this->reachedEndOfData || this->filledBufferNotOwnedByThisStream )
         return false;
      return true;
   }

   void enableHostNetworkEndianAutoConversion( bool performAutoEndianConversion ) { this->EnableHostNetworkEndianAutoConversion = performAutoEndianConversion; }
   bool enableHostNetworkEndianAutoConversion() { return this->EnableHostNetworkEndianAutoConversion; }

   ///////// Returns the number of extractable bytes from the current position to the beginning of the buffer.
   ///////// If the buffer contains the chars "abcdefghij" and currPos points at "d", this method will return
   /////////                                   0123456789
   ///////// the value 4. This is because the byte extraction operator can execute 4 more times before the buffer
   ///////// is empty. d,c,b,a would be returned, in that order.
   //////size_t getRemainingExtractableByteCount();

   ///////// Returns the number of insertable bytes from the current position to the end of the currently allocated 
   ///////// buffer. If this stream is resizable, the buffer will automatically resize when an insertion occurs after
   ///////// the corresponding number of bytes has been inserted; otherwise, the buffer will be full and will issue
   ///////// an error when attempting to insert into it.
   ///////// For example, if the buffer contains the chars "qrstuvwxyz" and currPos points at "x", this method will return
   /////////                                                0123456789
   ///////// the value 3. This is because the byte insertion operator can successfully overwrite the byte at location x, y,
   ///////// and z (in that order) before the buffer is full.
   //////size_t getRemainingInsertableByteCount();

   void displayWarningsToStdOut( bool showWarnings ) { this->ShowWarnings = showWarnings; }
   bool displayWarningsToStdOut() { return this->ShowWarnings; }

private:

   /// Resizes the internal array by a factor of sizeMultiplier if this instance owns 
   /// the internal array (created using default constructor); otherwise this method does nothing.
   void resizeBuffer( unsigned int sizeMultiplier = 2 );

   static const unsigned int DEFAULT_BUF_SIZE = 16384; ///< Default buffer is 16KB, will grow dynamically if owned

   /// True if the default constructor is used; false, if the user passes in his own buffer using the corresponding parameterized constructor
   bool ownsBuffer;

   char* bufPtr = nullptr; ///< Pointer to the start of the binary array. Not owned by this instance, don't delete unless explicitly told to do so in constructor
   unsigned int bufLen = 0; ///< Length of available memory for binary array, in bytes
   bool deleteInternalBufferOnDestruction = false; ///< Defaults to false, but can be forced to true by user if they are sure they want deletion on destruction
   
   char* currPos = nullptr; ///< Current read/write position into bufPtr. The next insert/extract will operate here.
   unsigned int currBufLen; ///< Current length from bufPtr of user specified binary data

   bool reachedEndOfData = false;
   bool filledBufferNotOwnedByThisStream = false;
   
   /// When true, big endian is sent over the network. That is data is converted to big endian on a stream insertion operation.
   /// Also, the data is then auto-converted back to the local machine-endian-ness on a stream extraction operation.
   /// When false, no endian-ness conversion is performed whatsoever.
   bool EnableHostNetworkEndianAutoConversion = true;

   bool ShowWarnings = false;

};

} //namespace Aftr

#endif
