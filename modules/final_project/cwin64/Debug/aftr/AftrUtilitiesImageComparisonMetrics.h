#pragma once

#include "AftrFrameCapture.h"
#include <vector>

namespace Aftr
{


class AftrUtilitiesImageComparisonMetrics
{
public:
    /**
   //Image comparison Metrics
   **/

   /// Computes RMS Luminance difference between image a and image b. A and B must be the same size and 
   /// their bytes per pixel must match
   static float calculateRMSLuminanceDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   static float calculateRMSLuminanceDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );

   /// "Haar Wavelet" style comparison using Mipmaps
   static float calculateWeightedMipmapDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   static float calculateWeightedMipmapDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );

   static float calculateCIELABEuclideanDeltaDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   static float calculateCIELABEuclideanDeltaDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );

   static float calculateHueAngleDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b, bool dynamicOnly, const std::vector< std::vector< bool > >& grid, std::string analysis = "hue.txt" );
   static float calculateHueAngleDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2, bool dynamicOnly, const std::vector< std::vector< bool > >& grid, std::string analysis = "hue.txt" );

   static float calculateSpatialHueAngleDifferenceBetweenTwoRGBImages( AftrFrameCapture* a, AftrFrameCapture* b, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );
   static float calculateSpatialHueAngleDifferenceBetweenTwoRGBImages( size_t width, size_t height, unsigned char* image1, unsigned char* image2, bool dynamicOnly, const std::vector< std::vector< bool > >& grid );

   static void processImageSpatialFilter( AftrFrameCapture* input, int id, double distanceMultiplier );

   /**
   //end image comparison metrics
   **/

};

}