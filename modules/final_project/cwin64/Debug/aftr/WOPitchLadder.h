#pragma once
#include "AftrConfig.h"

#include "WO.h"
#include <set>

namespace Aftr
{

   class WOQuad;
   class WOFTGLString;

   class WOPitchLadder : public WO
   {
   public:
      static WOPitchLadder* New( float width, float height, float vFov = 65.0f, unsigned int angleBetweenMarksDeg = 15 );
      virtual ~WOPitchLadder();
      virtual void onUpdateWO();
      virtual void setSource( WO* source ) { this->source = source; }
      virtual void setWorldNormal( const Vector& worldNormal );

      float getCurrentPitchFromHorizon(); ///< Returns pitch between [-90,90]
      float getCurrentRollFromHorizon();

   protected:
      WOPitchLadder( float vFov, unsigned int angleBetweenMarksDeg );
      virtual void onCreate( float width, float height );

      void computeVisiblePitchMarkers( float currPitch, std::vector< size_t>& markerIndices );
      size_t findSmallestPitchValIdxGreaterOrEqToVal( float minVisPitch );

      void createPitchLabels();
      void createNoseDirectionIndicator();

      Vector worldNormal;

      WO* source; ///< WO providing pitch ladder info

      class PitchMarker
      {
      public:
         PitchMarker( int deg, WOQuad* pitchBar = nullptr, WOFTGLString* left = nullptr, WOFTGLString* right = nullptr )
         { this->degree = deg; this->pitchBar = pitchBar; this->left = left; this->right = right; }

         int degree; ///< Degree above / below elevation this rung represents
         WOQuad* pitchBar; ///< Points at the ladder rung drawn at this pitch marker
         WOFTGLString* left; ///< Left label of this ladder rung
         WOFTGLString* right; ///< Right label of this ladder rung
      };

      std::vector< PitchMarker* > pitchLadder;
      WOQuad* noseDirection;

      Vector lastGoodSrcLookDir;

      float vFov; ///< The vertical field of view this pitch ladder uses to show its markers
      unsigned int angleBetweenMarksDeg; ///< Angle between each ladder mark, ie, 5,10,or 15 degrees between each rung
   };

} //namespace Aftr

