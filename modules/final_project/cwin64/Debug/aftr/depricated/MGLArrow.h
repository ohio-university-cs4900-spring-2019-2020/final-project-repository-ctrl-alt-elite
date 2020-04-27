#pragma once

#include "MGL.h"

/**

   \class MGLArrow
   \author Chad Mourning
   \brief An MGL that create an arrow that can blink, follow an object, or stay constant size with distance.

*/

namespace Aftr
{
   class Camera;
   class IndexedGeometrySphere;
   class IndexedGeometryCylinder;
   class WO;

   class MGLArrow : public MGL
   {
   public:
      /**
      
      /param scale Size multiplier for all dimensions of the arrow.
      /param color Color of the arrow
      /param scaleWithDistance If true, the arrow is the same size no matter where on the screen it is, otherwise behaves like a normal object.
      /param cam Pointer to a camera, used with scaleWithDistance

      */
      MGLArrow( WO* parentWO, float scale, Vector color, bool scaleWithDisatance, Camera** cam);
      ///destructor, kills quadric
      virtual ~MGLArrow();
      ///renders arrow
      virtual void render( const Camera& cam );
      ///this object has a correct bounding box and as such implements a proper
      ///frustum culling method
      virtual bool isInViewingFrustum( const AftrGeometryFrustum& viewportFrustum );
      ///mutator for the followee
      void setFollowee(WO* followee) { this->followee = followee; }
      ///accessor for the followee
      WO* getFollowee() { return followee; }
   protected:
      ///a camera pointer (needed to scale with distance)
      Camera** cam;
      ///adjusts size of arrow
      float scale;
      ///the rgb values for this arrow
      Vector color;
      ///if true the arrow will remain the same size at all times, otherwise acts like a normal object
      bool scaleWithDistance;   
      ///the WO that the arrow is attached to
      WO* followee;

      IndexedGeometrySphere* sphere;
      IndexedGeometryCylinder* cylinder;
   };

}

