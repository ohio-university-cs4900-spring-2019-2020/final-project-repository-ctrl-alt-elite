#pragma once

#include <vector>
#include <cstddef>

namespace Aftr
{

class WO;

/**
   \author Scott Nykl
   \brief Wrapper around std::vector< WO* > used by WOs to store children.

   This wraps an std::vector and adds in specific hooks to notify other systems,
   such as the WorldContainer instance, when a new child WO is inserted into the
   list.
*/
class WorldObjectChildContainer
{
public:
   WorldObjectChildContainer();
   ~WorldObjectChildContainer();
   void setParentWO( WO* wo );

   /**
      Overloaded for children WOs. When a child is inserted into a parent's childList
      (this list), this overloaded push_back(...) inserts the child into the parent's
      list and notifies the WorldContainer that a child has been inserted into a
      parent.

      This method also sets the child's parent WO* to the WO which contains this list
      prior to inserting. This enforces that the child's parentWO is set properly.
   */
   void push_back( WO* child );

   //virtual void clear();

   /**
      This method removes the WO* from this container and it also notifies the
      world container that this WO* has been removed. This notification lets 
      smart WorldContainers such as the octree know that the Meshes and Models
      corresponding to this WO* can be removed.
   */
   bool eraseViaWOptr( WO* wo );
   bool eraseViaWOIndex( size_t index );

   //Methods that wrap std::vector
   size_t size() const;
   size_t max_size() const;
   void resize( size_t newSize );
   size_t capacity() const;
   bool empty() const;
   void reserve( size_t n );

   WO* at( size_t i ) const; ///< accesses i'th element within rhs of expression
   WO* at( size_t i );
   std::vector<WO*>::iterator at_iter( size_t i );

   WO* operator[] ( size_t i ) const; ///< accesses i'th element within rhs of expression
   WO* operator[] ( size_t i );
   void clear();
   void pop_back();


private:

   std::vector< WO* > list; ///< internal std::vector which stores the WO*
   WO* parentWO;
};


} //namespace Aftr

