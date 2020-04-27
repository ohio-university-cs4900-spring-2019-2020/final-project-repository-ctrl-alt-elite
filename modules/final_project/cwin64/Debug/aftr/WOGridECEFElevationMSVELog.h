#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_GDAL

#include "WOGridECEF.h"
#include "VectorFwd.h"

namespace Aftr
{

   class WOGridECEFElevationMSVELog : public WOGridECEF
   {
   public:
      static WOGridECEFElevationMSVELog* New( int latChunks, int lonChunks, const std::string& elevationData, const std::string& textureLog, const VectorD& offsetInLLA, const VectorD& upperLeft, const VectorD& lowerRight, const std::vector< std::vector< VectorD > >& pointsForTerrain = std::vector< std::vector< VectorD > >());
      virtual ~WOGridECEFElevationMSVELog();
   protected:
      WOGridECEFElevationMSVELog();
      virtual void onCreate( int latChunks, int lonChunks, const std::string& elevationData, const std::string& textureLog, const VectorD& offsetInLLA, const VectorD& upperLeft, const VectorD& lowerRight, const std::vector< std::vector< VectorD > >& pointsForTerrain );
   };

}

#endif
