#pragma once
#include <iostream>
#include <map>

namespace Aftr
{

template < typename L, typename R >
class AftrBimap
{
public:

   AftrBimap();
   AftrBimap( const AftrBimap& toCopy );
   virtual ~AftrBimap();

   void clear();
   size_t size();

   bool updateAtLeftKey( const L& leftKey, const R& newRightValue );
   bool updateAtRightKey( const R& rightKey, const L& newLeftValue );

   bool insert( const L& left, const R& right );

   bool removeUsingLeftKey( const L& leftKey );
   bool removeUsingRightKey( const R& rightKey );

   AftrBimap< L, R >& operator =( const AftrBimap<  L,  R >& m );

   typename std::map< L, R >::iterator findUsingLeftKey( const L& leftKey );
   typename std::map< R, L >::iterator findUsingRightKey( const R& rightKey );

   typename std::map< L, R >::iterator endIteratorLeft();
   typename std::map< R, L >::iterator endIteratorRight();

   typename std::map< L, R > getLeft() { return this->left; }
   typename std::map< R, L > getRight() { return this->right; }

protected:
   std::map< L, R > left;
   std::map< R, L > right;

};


}
#include "AftrBimap.cpptemplate.h"
