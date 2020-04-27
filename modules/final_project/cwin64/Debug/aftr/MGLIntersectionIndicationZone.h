#pragma once

#include "MGL.h"

namespace Aftr
{

   class MGLIntersectionIndicationZone : public MGL
   {
   public:
      static MGLIntersectionIndicationZone* New(WO* parent, const Vector& extents, const std::vector< WO* >& occluders );
      virtual ~MGLIntersectionIndicationZone( );
      virtual void render(const Camera& cam);
      void increaseResolution(unsigned int x);//add way to decrease later

      std::vector< VectorD > pointsToTest;
	  void setTerrain(WO* terrain) { this->terrain = terrain; }

   protected:

      class Node
      {
      public:
         enum Direction { NORTH_NORTHEAST, EAST_SOUTHEAST, SOUTH_SOUTHWEST, WEST_NORTHWEST, MAX_DIRECTIONS  };

         Node( const Vector& center, const Vector& extents, const Vector& color );
         void accumulateRenderInfo(std::vector< Vector >& vertices, std::vector< unsigned int >& indices, std::vector< Vector >& colors);
         ~Node();
         Node* increaseResolution( unsigned int maxDepth);
         Vector center;
         Vector extents;
         Vector color;
         Node* northeast;
         Node* northwest;
         Node* southeast;
         Node* southwest;
         //Node* parent;
      };

      Node* root;
      Node* next;
      Vector center;
      Vector extents;
      Vector gravityDirection;
      WO* terrain;
      std::vector< WO* > occluders;
      virtual void onCreate();
      MGLIntersectionIndicationZone(WO* parent, const Vector& center, const Vector& extents, const std::vector< WO* >& occluders);

   };

}