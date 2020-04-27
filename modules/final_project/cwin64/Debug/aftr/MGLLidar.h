#pragma once

#include "MGL.h"

namespace Aftr
{

class WOGhostLidar;

class MGLLidar : public MGL
{
public:
   MGLLidar( float angleDeg, float height, WOGhostLidar* wo );
   virtual ~MGLLidar();

   virtual void render( const Camera& cam );

   void setAngleDegOfSpread( float angle );
   void setHeight( float heightOfScanBeam );
   float getAngleDegOfSpread() { return this->angleDeg; }
   float getHeight() { return this->height; }
   
   /**
      Returns transformed vector pointing in direction of the right most vertex
      assuming eye is looking along the LIDAR's lookDirection and the eye's UP
      vector is the LIDAR's normalDirection.
   */
   Vector getEdge0Direction();
   
   /**
      Returns transformed vector pointing in direction of the left most vertex
      assuming eye is looking along the LIDAR's lookDirection and the eye's UP
      vector is the LIDAR's normalDirection.
   */
   Vector getEdge1Direction();

   void isRenderingLidarHitFaces( bool renderHitFaces ) { this->IsRenderingLidarHitFaces = renderHitFaces; }
   bool isRenderingLidarHitFaces() { return this->IsRenderingLidarHitFaces; }
   
protected:

   void updatePoints();
   void renderHitFaces();

   WOGhostLidar* wo;
   bool IsRenderingLidarHitFaces;
   float angleDeg;
   float height;
   Vector pt0;
   Vector pt1;

};

} //namespace Aftr

