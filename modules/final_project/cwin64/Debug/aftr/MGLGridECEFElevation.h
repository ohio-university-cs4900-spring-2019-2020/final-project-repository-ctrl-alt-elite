#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL

#include "MGLGridECEF.h"

namespace Aftr
{
class MGLGridECEFElevation : public MGLGridECEF
{
public:
   /// Offset is typically the center LLA point for the terrain...
   MGLGridECEFElevation( WO* parentWO, bool clip, const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& offset, const VectorD& scale, const std::string& elevationData, float exageration );

   /// Offset is typically the center LLA point for the terrain...
   MGLGridECEFElevation( WO* parentWO,            const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& offset, const VectorD& scale, const std::string& elevationData, float exageration );
   
   /// Offset is typically the center LLA point for the terrain...
   MGLGridECEFElevation( WO* parentWO, const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& scale, const std::string& elevationData, float exageration );
   virtual ~MGLGridECEFElevation() {}
   //virtual void defineVertices();
   //virtual void defineTextureCoords();
   virtual void defineTextureCoordsClipped();
   virtual void defineColors();
  // virtual void render( const Camera& cam );
   virtual void setScale( const Vector& scale );

   float oceanHeight;

   virtual bool overTerrainLLA( Vector lla );
   virtual double getElevationAtLLA( Vector lla );
protected:
   void createNewResolutionTerrain( const VectorD& upperLeft, const VectorD& lowerRight, const std::string& elevationData );
   void createFullResolutionTerrain( const VectorD& upperLeft, const VectorD& lowerRight, const std::string& elevationData );
   void createSubSampledTerrain( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const std::string& elevationData );

   float maxHeight;
   float minHeight;

   float averageHeight;
   float standardDeviationHeight;
};
}

#endif

