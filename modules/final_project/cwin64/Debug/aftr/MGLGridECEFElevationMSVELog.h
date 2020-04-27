#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL

#include "MGLGridECEF.h"

namespace Aftr
{

   struct TextureDensityDatumLLA;

   class MGLGridECEFElevationMSVELog : public MGLGridECEF
   {
   public:
      static MGLGridECEFElevationMSVELog* New( WO* parent, int latChunks, int lonChunks, const std::string& elevationData, const std::string& textureLog, const VectorD& offsetInLLA, const VectorD& upperLeft, const VectorD& lowerRight, const std::vector< std::vector< VectorD > >& pointsForTerrain );
      virtual ~MGLGridECEFElevationMSVELog();
      //virtual void defineIndices();
      //virtual void defineVertices();
      //virtual void defineTextureCoords();
      //virtual void defineNormals();
      //virtual void defineColors();
      virtual void makeVBO(int splits = 0);
     
   protected:
      struct UnifiedEntry
      {
         UnifiedEntry(){}
         UnifiedEntry( double lat, double lon, double elevation, double x, double y );
         double lat;
         double lon;
         double elevation;
         double x;
         double y;
       std::string toString() const;
      };

      MGLGridECEFElevationMSVELog( WO* parent );
      virtual void onCreate( int latChunks, int lonChunks, const std::string& elevationData, const std::string& textureLog, const VectorD& offsetInLLA, const VectorD& upperLeft, const VectorD& lowerRight, const std::vector< std::vector< VectorD > >& pointsForTerrain );
      void createTextureData( const std::string& elevationData, const std::string& textureLog, const VectorD& upperLeft, const VectorD& lowerRight, const std::vector< std::vector< VectorD > >& pointsForTerrain );
      void createVertexData();

      //there will be latChunks * lonChunks meshes in the final object
      int latChunks;
      int lonChunks;
      VectorD offsetInLLA;
      std::vector< std::vector< std::vector< UnifiedEntry > > > chunkedVertices;

       std::vector< std::vector< VectorD > > extractCornersFromTextureDensityFunction( const std::vector< std::vector< TextureDensityDatumLLA > >& textureDensityFunction );
       std::vector< std::vector< MGLGridECEFElevationMSVELog::UnifiedEntry > > createUnifiedGrid( const std::vector< std::vector< TextureDensityDatumLLA > >& textureDensityFunction, const std::string& elevationData, const VectorD& upperLeft, const VectorD& lowerRight, const std::vector< std::vector< VectorD > >& pointsForTerrain );
       std::vector< std::vector< std::vector< MGLGridECEFElevationMSVELog::UnifiedEntry > > > chunkGridBasedOnCorners( const std::vector< std::vector< MGLGridECEFElevationMSVELog::UnifiedEntry > >& unifiedGrid /*, const std::vector< std::vector< VectorD > >& corners*/ );
       std::vector< unsigned int > generateIndexScheme( const std::vector< std::vector< UnifiedEntry > >& vertexList );
       UnifiedEntry sampleTexture( const std::vector< std::vector< TextureDensityDatumLLA > >& textureDensityFunction, const VectorD& samplePoint );
   };

}

#endif
