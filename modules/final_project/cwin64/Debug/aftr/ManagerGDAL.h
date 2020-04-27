#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL

#include <string>
#include <vector>
#include "VectorFwd.h"

class GDALDataset;

namespace Aftr
{


   //used for GDAL initialization and parsing files
class ManagerGDAL
{
public:
   static void init();
   static void shutdown();
  //reads extents from file, so they can be used later
   static void getExtentsFromFile( const std::string& filename, double& upper, double& lower, double& left, double& right );

   //reads extents from file, don't need passed in
   static std::vector< std::vector< VectorD > > parseGDALTifAssumingGeodesicSpacing( const std::string& elevationData );
   static std::vector< std::vector< VectorD > > parseGDALTifAssumingGeodesicSpacingClipped( const std::string& elevationData, const VectorD& upperLeft, const VectorD& lowerRight );
   static std::vector< std::vector< VectorD > > parseGDALTifAssumingLinearSpacing( const std::string& elevationData, const VectorD& upperLeft, const VectorD& lowerRight );
   static std::vector< std::vector< VectorD > > parseGDALTifAssumingLinearSpacingAtThesePoints( const std::string& elevationData, const VectorD& upperLeft, const VectorD& upperRight, const std::vector< std::vector< VectorD > >& pointsToSample );
   static std::vector< std::vector< VectorD > > parseGDALTifAssumingGeodesicSpacing( const std::string& elevationData, const VectorD& upperLeft, const VectorD& lowerRight );
   static void calculateGridStatistics( double& min, double& max, double& mean, double& stddev, const std::vector< std::vector< VectorD > >& grid );


protected:
   ///returns the elevation data and resizes the grid correctly
   static float* loadElevation( GDALDataset* poDataset );
   static float* loadElevation( const std::string& elevationData, std::vector< std::vector< VectorD > >& grid );
   static void populateGridElevation( float* elevation, std::vector< std::vector< VectorD > >& grid );
};

}

#endif
