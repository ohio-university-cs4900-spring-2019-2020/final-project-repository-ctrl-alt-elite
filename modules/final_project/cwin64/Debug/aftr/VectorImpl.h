#pragma once
#include <vector>
#include <string>

//This is a implementation file used by the templated Vector class. The primary purpose of this 
//class is to form a compilation firewall for the Ve
namespace Aftr
{

namespace VectorImpl
{

//Wraps the call to AftrUtilites, so Vector.h does NOT have to actually include AftrUtilities.h (huge header)
std::string encodeBinaryToBase64( const std::vector<unsigned char>& data );

//Wraps the call to AftrUtilites, so Vector.h does NOT have to actually include AftrUtilities.h (huge header)
/// Any extra padding at the end "==" or "=" will be ignored when converting to binary.
std::vector< unsigned char > encodeBase64ToBinary( const std::string& base64Str );
   
}

}
