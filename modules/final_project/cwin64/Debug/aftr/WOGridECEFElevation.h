#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL

#include "WOGridECEF.h"

namespace Aftr
{
class WOGridECEFElevation : public WOGridECEF
{
public:
   static WOGridECEFElevation* New( bool clip, const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& offset, const VectorD& scale, std::string elevationData, int splits = 2, float exageration = 0, bool useColors = false );
   static WOGridECEFElevation* New( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& offset, const VectorD& scale, std::string elevationData, int splits = 2, float exageration = 0, bool useColors = false );
   static WOGridECEFElevation* New( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& scale, std::string elevationData, int splits = 2, float exageration = 0, bool useColors = false, float oceanHeight = -1500 );
   virtual ~WOGridECEFElevation();
   virtual bool overTerrainLLA( Vector lla );
   virtual double getElevationAtLLA( Vector lla );
   VectorD getCenterLLA() { return this->centerLLA; }
protected:
   virtual void onCreate( bool clip, const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& offset, const VectorD& scale, std::string elevationData, int splits, float exageration, bool useColors );
   virtual void onCreate( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& offset, const VectorD& scale, std::string elevationData, int splits, float exageration, bool useColors );
   virtual void onCreate( const VectorD& upperLeft, const VectorD& lowerRight, unsigned int granularity, const VectorD& scale, std::string elevationData, int splits, float exageration, bool useColors, float oceanHeight );
   WOGridECEFElevation();
   VectorD centerLLA;
};
}

#endif

