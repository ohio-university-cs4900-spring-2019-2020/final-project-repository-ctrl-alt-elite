#pragma once

#include <string>

namespace Aftr
{

class AftrADSBComMsg
{
public:
   AftrADSBComMsg();
   virtual ~AftrADSBComMsg();
   std::string toString() const;
   std::string toStringNoChecksum() const;
   unsigned int computeChecksum() const;

   /**
      Returns a binary array of length BINARY_MSG_LEN_BYTES in big endian format. This
      raw data is useful for sending over network connections of other binary
      comm links. The returned char array is owned by the caller and is not deleted
      by this instance.
      The format of the message is exactly 25 bytes:
      Each message has one start byte '#', 2 doubles (lat, lng), 1 float (elevation), and 1 unsigned int (checksum)
      totalling 25 bytes:
      #aaaaaaaannnnnnnneeeecccc
      Where 'a' are latitude bytes (big endian) (form a double)
      Where 'n' are longitude bytes (big endian) (form a double)
      Where 'e' are elevation bytes (big endian) (form a float)
      Where 'c' are checksum bytes (big endian) (form an unsigned int)
   */
   char* toBinaryArrayBigEndian() const;

   /**
      Given raw big endian of length BINARY_MSG_LEN_BYTES bytes, this method constructs the
      and returns the resulting AftrADSBComMsg. Optionally (if not NULL), the outChecksum
      is set to the checksum contained within the binary data and may be used to 
      verify validity against the new msg's computeChecksum() method.
   */
   static AftrADSBComMsg fromBinaryArrayBigEndian( char* binDataOfProperLen, unsigned int* outChecksum = NULL );

   static const unsigned int BINARY_MSG_LEN_BYTES = 25;

   double lat; ///< WGS 84 latitude (decimal value)
   double lng; ///< WGS 84 longitude (decimal value)
   float elevation; ///< Elevation in feet
protected:
};

} //namespace Aftr

