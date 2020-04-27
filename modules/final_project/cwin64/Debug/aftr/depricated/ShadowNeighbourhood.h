#pragma once

#include <vector>
#include "SteamieGeometryPlane.h"

namespace Steamie
{

   class SteamieGeometryPlane;

   /**

   \class ShadowNeighbourhood
   \author Chad Mourning
   \brief A data structure to aid in the creation of shadow volumes.

   This is the data structure used to map out a model so it can be used in the shadow
   volume system.

   */

class ShadowNeighbourhood
{
   friend class IFaceShadowCaster;
   friend class WOLightShadowCasting;
public:
   /**

   Default constructor.  Assigns dispMatrix to NULL.

   */
   ShadowNeighbourhood();
   /** The plane equation of this neighbourhood object */
   SteamieGeometryPlane plane;
   /**
   
   The three neighbours of this neighbourhood object.

   neighbours[0] is the member of the neighbourhood that shares the edge created by
   points[0] and points[1].

   neighbours[1] is the member of the neighbourhood that shares the edge created by
   points[1] and points[2].

   neighbours[2] is the member of the neighbourhood that shares the edge created by
   points[2] and points[0].

   */
   int neighbours[3];
   /**

   The three points of this face.  Winds in the CCW direction.

   */
   int points[3];
   /**

   The display matrix need to alighn this face with the keyface of its shadow network.

   */
   float* dispMatrix;

   /**

   The only member that changes post initialization.

   If true, this face is visible to the light.  

   If false, this face is not visible to the light.

   */
   bool visible;
};

}

