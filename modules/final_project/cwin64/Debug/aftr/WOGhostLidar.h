#pragma once

#include "WO.h"
#include "MGLLidar.h"

namespace Aftr
{

class WOGhostLidar : public WO
{
public:
   friend class MGLLidar;
   static WOGhostLidar* New( float angleDeg, float height );
   virtual ~WOGhostLidar();

   void startScanOfTerrain();
   void endScanOfTerrain();

   virtual void onUpdateWO();

   void setLidarSweepAngle( float sweepAngleDeg );
   void setLidarAngleOfSpread( float spreadAngleDeg );
   void setLidarBeamLength( float lidarBeamLength );
   void setLidarSweepVelocityInDegPerUpdate( float degPerUpdate );
   void setLidarSweepPeriod( float timeInMS );
   float getLidarSweepPeriod() { return this->periodInMS; }

   float getLidarAngleOfSpread() { return ((MGLLidar*)this->model)->getAngleDegOfSpread(); }
   float getLidarSweepVelocityInDegPerUpdate() { return this->sweepVelocityDegreesPerUpdate; }

   void isRenderingLidarHitFaces( bool renderHitFaces ) { ((MGLLidar*)this->model)->isRenderingLidarHitFaces( renderHitFaces ); }
   bool isRenderingLidarHitFaces() { return ((MGLLidar*)this->model)->isRenderingLidarHitFaces(); }

   /**
      Returns transformed vector pointing in direction of the right most vertex
      assuming eye is looking along the LIDAR's lookDirection and the eye's UP
      vector is the LIDAR's normalDirection.
   */
   Vector getEdge0Direction() { return ((MGLLidar*)this->model)->getEdge0Direction(); }
   
   /**
      Returns transformed vector pointing in direction of the left most vertex
      assuming eye is looking along the LIDAR's lookDirection and the eye's UP
      vector is the LIDAR's normalDirection.
   */
   Vector getEdge1Direction() { return ((MGLLidar*)this->model)->getEdge1Direction(); }

   bool addLidarSink( WO* wo );
   WO* getLidarSinkAt( size_t i );
   size_t getLidarSinkCount();

   float* getLidarSinkVertsAt( size_t i );
   unsigned int getLidarSinkVertCountAt( size_t i );
   unsigned int* getLidarSinkIndiciesAt( size_t i );
   unsigned int getLidarSinkIndexCountAt( size_t i );
   unsigned char* getLidarSinkOutputIndexHitsAt( size_t i );
   void setLidarSinkOutputIndexHitsAt( size_t i, unsigned char* resultListPtr );
   //std::vector< WO* >* getLidarSinks() { return &this->lidarSinks; }

protected:
   WOGhostLidar();
   virtual void onCreate( float angleDeg, float height );

   bool isScanning;
   float sweepAngle;
   unsigned int lastUpdateTime;
   float periodInMS;
   float sweepVelocityDegreesPerUpdate;
   bool isFirstScan;
   float initialChangeDeltaPhiWRTJointAngle;
   enum SCAN_STATE { SWEEPING_BACK, SWEEPING_FRONT };
   SCAN_STATE scanState;

   std::vector< WO* > lidarSinks;

   //C-style storage used by the Vert/Index getter methods.
   //AnyVectorBelow[x] corresponds to the WO* at lidarSinks[x].
   //Implemented this way only because CUDA requires old-school C arrays,
   //and is not OO and cannot understand the STL.
   std::vector< float* > verts; //vector of float arrays. verts[x] is the xth vertex list
   std::vector< unsigned int > vertCount; //vertCount[x] is the number of floats in the vert[x] vertex list
   std::vector< unsigned int* > indicies; //array of unsigned int arrays. indicies[x] is the xth index list
   std::vector< unsigned int > indexCount; //indexCount[x] is the number of ints in the indicies[x] indicies list
   std::vector< unsigned char* > outputIndexHits; //outputIndexHits[x] is a list of indicies[x] that are currently colliding

};

} //namespace Aftr

