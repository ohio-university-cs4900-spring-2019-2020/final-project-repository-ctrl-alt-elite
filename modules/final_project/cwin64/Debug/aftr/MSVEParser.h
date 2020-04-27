#pragma once

#include <string>
#include <vector>

namespace Aftr
{

class WO;

struct FourCorners
{
   double upper;
   double lower;
   double left;
   double right;
};

struct TextureDensityDatumLLA
{
   TextureDensityDatumLLA(){}
   TextureDensityDatumLLA( double lat, double lon, double y, double x );
   double lat;
   double lon;
   double x;
   double y;
};

class MSVEParser
{
public:
   MSVEParser();
   std::vector< std::vector< TextureDensityDatumLLA > > parse( const std::string& filename );
protected:
};

} //namespace Aftr
