#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL

#include <vector>
#include <string>
#include "VectorFwd.h"


namespace Aftr
{
   class WO;

   class TerrainChunker
   {
   public:
      TerrainChunker();
      std::vector< WO* > chunk( const std::string& terrainElevation, size_t latDim, size_t lonDim, const VectorD& upperLeft, const VectorD& upperRight, const VectorD& offsetInLLA );
      std::vector< WO* > chunk( const std::vector< std::vector< VectorD > >& gridInLLA, size_t latDim, size_t lonDim, const VectorD& offsetInLLA );
      std::vector< std::vector< std::vector< VectorD > > > chunk( const std::vector< std::vector< VectorD > >& gridInLLA, size_t latDim, size_t lonDim );
   protected:
      void populateFullGrid( const std::string& terrainElevation, const VectorD& upperLeft, const VectorD& upperRight, std::vector< std::vector< VectorD > >& fullGrid );
      std::vector< WO* > createObjects( size_t latDim, size_t lonDim, const std::vector< std::vector< VectorD > >& fullGrid, const VectorD& offsetInLLA );

      std::vector< std::vector< std::vector< std::vector< VectorD > > > > getGridOfGridsPortions( const std::vector< std::vector< VectorD > >& fullGrid, int latDim, int lonDim );
      std::vector< std::vector< std::vector< std::vector< VectorD > > > > getGridOfGridsActual( const std::vector< std::vector< VectorD > >& fullGrid, int latDim, int lonDim );
   };

}

#endif
