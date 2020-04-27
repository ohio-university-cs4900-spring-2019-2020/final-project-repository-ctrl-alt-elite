#pragma once

#include <vector>
#include "WorldContainer.h"

namespace Aftr
{

class WO;
class Camera;

/**

\class WorldList
\author Chad Mourning
\brief This is the class that manages intelegent operations on the list of world objects.

This is the class that manges intelegent operations, such as sorting, on the list of world objects.
Between renders the world is resorted to aid in proper display of transparent objects.  It also
maintains a copy of the original world list in case it is needed.  It replicates most of the
functions of a std::vector for easy use.  Sorting is done by the distanceMetric function.  If this
function is overloaded in an inherited class you can sort your objects in a different order.

Sorting relies on the Aftr::renderOrderType to do its sorting.  RENDER_ORDER_TYPE::roLIGHT objects are always put
in the list first.  These are followed by RENDER_ORDER_TYPE::roOPAQUE.  The RENDER_ORDER_TYPE::roTRANSPARENT objects are sorted according
to the distance metric and then put in the list.  RENDER_ORDER_TYPE::roOVERLAY objects are always put in the list last.

Note: removing and adding items from/to the list after loadMap may break the original list.

*/

class WorldList : public WorldContainer
{
public:
   /**
      The default constructor for the world list.
   */
   WorldList( bool enableSortingOnUpdate = true );

   /**
      The destructor for the WorldList.
      Clears the current and original lists.  Does NOT destroy the objects in the list.
   */
   virtual ~WorldList();

   virtual void update( const Camera& cam );

   /**
      \param loc The location of the camera
      \param lookAt The lookAt direction of the camera

      Reorders the list such that all RENDER_ORDER_TYPE::roLIGHT objects come first, followed by
      all RENDER_ORDER_TYPE::roOPAQUE objects, followed by RENDER_ORDER_TYPE::roTRANSPARENT objects sorted by distanceMetric,
      followed by the RENDER_ORDER_TYPE::roOVERLAY objects.
   */
   void sortList(const Vector& loc, const Vector& lookAt);
   
   ///issues a request to do a full sort on the next pass
   void sortList() { sortListNextPass = true; }

   virtual void renderWorld( const Camera& cam );

   void isSortingOnUpdate( bool isSorting ) { this->enableSorting = isSorting; }

   size_t getIndexWhereTransparentWOsStart() { return this->indexWhereTransparentObjectsStart; }
   size_t getIndexWhereTransparentWOsEnd() { return this->indexWhereTransparentObjectsEnd; }

   virtual bool eraseViaWOptr( WO* wo );
   virtual bool eraseViaWOIndex( size_t index );

   //overloaded to help control sorting behavior
   virtual void push_back(WO* wo);

protected:
   /**
      \param lock The location of the camera
      \param lookAt The look direction of the camera
      \param x The object that you are measuring

      The base distance metric function.  It is a simply distance from the camera to the fixed point of the object.
      This function can be overriden in children functions to behave differently.
   */
   virtual float distanceMetric( const Vector& lock, const Vector& lookAt, WO* x);

   /**
      A full should be called when some action occurs that changes the total number of objects in the world list
      or changes the transparency type of an object already in the world list
   */
   void fullSort( const Aftr::Vector& loc, const Aftr::Vector& lookAt );
   void shortSort( const Aftr::Vector& loc, const Aftr::Vector& lookAt );

   bool sortListNextPass;
   size_t indexWhereTransparentObjectsStart;
   size_t indexWhereTransparentObjectsEnd;

   bool enableSorting = true;
};

}

