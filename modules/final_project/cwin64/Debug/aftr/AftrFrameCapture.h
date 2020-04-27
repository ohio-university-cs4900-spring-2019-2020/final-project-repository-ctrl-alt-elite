#pragma once

#include <string>
#include <vector>

namespace Aftr
{

class AftrFrameCapture
{
public:
   AftrFrameCapture();
   virtual ~AftrFrameCapture();

   std::string toString() const;
   void setFrameData( unsigned int width, unsigned int height, unsigned int Bpp, char* pixelData, const std::string& fileName = "", bool flipVertical = true, bool takesOwnershipOfPixelData = true );
   bool toFile( const std::string& fileName, bool transposeBGRtoRGB = false ) const;
   bool toFile( bool transposeBGRtoRGB = false ) const;
   bool fromFile( const std::string& fileName );

   const std::string& getFileName() const { return this->fileName; }
   void setFileName( const std::string& fileName ) { this->fileName = fileName; }

   char* getPixelData() { return this->pixelData; }
   void flipFrameDataVertically();
   unsigned int getWidth() { return this->width; }
   unsigned int getHeight() { return this->height; }
   unsigned int getBytesPerPixel() { return this->Bpp; }
   unsigned int getSizeInBytes() const { return this->width * this->height * this->Bpp; }

   float calculateRMSLuminanceDifference( AftrFrameCapture* cap, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   float calculateWeightedMipmapDifference( AftrFrameCapture* cap, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   float calculateCIELABDeltaEpsilon( AftrFrameCapture* cap, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   float calculateHueAngleMetric( AftrFrameCapture* cap, bool dynamicOnly, const std::vector< std::vector< bool > >& grid, std::string analysis = "analysis.txt" );
   float calculateSpatialHueAngleMetric( AftrFrameCapture* cap, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );


protected:

   bool ownsPixelData = true; ///< Set by user when calling setFrameData. If this is false, destructor will not delete this.pixelData
   char* pixelData = nullptr; ///< raw rgb data, size is bytes per pixel * width * height
   unsigned int width = 0; ///< Width of this frame in pixels
   unsigned int height = 0; ///< Height of this frame in pixels
   unsigned int Bpp = 0; ///< Bytes per pixel, (typically red, green, blue ) = 3 bytes for color
   std::string fileName = "";
};

} //namespace Aftr

