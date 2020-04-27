#pragma once

namespace Aftr
{

   template < typename L, typename R > 
   AftrBimap< L, R >::AftrBimap()
   {
      this->left.clear();
      this->right.clear();
   }

   template < typename L, typename R > 
   AftrBimap< L, R >::AftrBimap( const AftrBimap& toCopy )
   {
      (*this) = toCopy;
   }

   template < typename L, typename R > 
   AftrBimap< L, R >::~AftrBimap()
   {
      this->left.clear();
      this->right.clear();
   }

   template < typename L, typename R > 
   void AftrBimap< L, R >::clear()
   {
      this->left.clear();
      this->right.clear();
   }

   template < typename L, typename R > 
   size_t AftrBimap< L, R >::size()
   {
      return this->left.size();
   }

   template < typename L, typename R > 
   bool AftrBimap< L, R >::updateAtLeftKey( const L& leftKey, const R& newRightValue )
   {
      //Get iterator to left map
      typename std::map< L, R >::iterator lit = this->left.find( leftKey );
      if( lit != this->left.end() )
      {
         //Get iterator to right map
         typename std::map< R, L >::iterator rit = this->right.find( lit->second );
         if( rit != this->right.end() )
         {
            //std::cout << "Found bidirectional mapping...Updating right side\n";
            this->right.erase( rit );
            this->right.insert( std::make_pair( newRightValue, leftKey ) ); //update right map
            lit->second = newRightValue; //update left map
            return true;
         }
         else
            std::cout << "Failed to updateAtLeftKey:\n"
                      << "   Right map does not contain key '" << /*lit->second*/" " << "'\n";
      }
      else
         std::cout << "Failed to updateAtLeftKey:\n"
                   << "   Left map does not contain key '" << /*leftKey*/" " << "'\n";

      return false;
   }

   template < typename L, typename R > 
   bool AftrBimap< L, R >::updateAtRightKey( const R& rightKey, const L& newLeftValue )
   {
      //Get iterator to right map
      typename std::map< R, L >::iterator rit = this->right.find( rightKey );
      if( rit != this->right.end() )
      {
         //Get iterator to left map
         typename std::map< L, R >::iterator lit = this->left.find( rit->second );
         if( lit != this->left.end() )
         {
            //std::cout << "Found bidirectional mapping...Updating left side\n";
            this->left.erase( lit );
            this->left.insert( std::make_pair( newLeftValue, rightKey) ); //update left map
            rit->second = newLeftValue; //update right map
            return true;
         }
         else
            std::cout << "Failed to updateAtRightKey:\n"
                      << "   Left map does not contain key '" << rit->second << "'\n";
      }
      else
         std::cout << "Failed to updateAtRightKey:\n"
                   << "   Right map does not contain key '" << rightKey << "'\n";

      return false;
   }

   template < typename L, typename R > 
   bool AftrBimap< L, R >::insert( const L& left, const R& right )
   {
      //insert into left map
      std::pair< typename std::map< L, R >::iterator, bool > retLeft = this->left.insert( std::make_pair( left, right ) );
      //if( retLeft.second )
      //{
      //   std::cout << "Inserted left...\n";
      //}
      //else
      //{
      //   std::cout << "Left key already exists... R-value is " << retLeft.first->second << "\n";
      //}

      //insert into right map
      std::pair< typename std::map< R, L >::iterator, bool > retRight = this->right.insert( std::make_pair( right, left ) );
      //if( retRight.second )
      //{
      //   std::cout << "Inserted right...\n";
      //}
      //else
      //{
      //   std::cout << "Right key already exists... L-value is " << retRight.first->second << "\n";
      //}


      if( ! retLeft.second || ! retRight.second )
      {
         std::cout << "Failed to insert into bimap...\n";
         if( ! retLeft.second )
            std::cout << "   Left key already exists...\n";
         if( ! retRight.second )
            std::cout << "   Right key already exists...\n";

         if( retLeft.second )
            this->left.erase( retLeft.first );
         if( retRight.second )
            this->right.erase( retRight.first );

         return false;
      }

      return true;
   }

   template < typename L, typename R > 
   bool AftrBimap< L, R >::removeUsingLeftKey( const L& leftKey )
   {
      //Get iterator to left map
      typename std::map< L, R >::iterator lit = this->left.find( leftKey );
      if( lit != this->left.end() )
      {
         //Get itator to right map
         typename std::map< R, L >::iterator rit = this->right.find( lit->second );
         if( rit != this->right.end() )
         {
            //std::cout << "Found bidirectional mapping... Removing using left key...\n";
            this->left.erase( lit );
            this->right.erase( rit );
            return true;
         }
         else
            std::cout << "Failed to removeUsingLeftKey...\n"
                      << "   Right map does not contain key corresonding to left-map data\n";
      }
      else
         std::cout << "Failed to removeUsingLeftKey...\n"
                   << "   Left map does not contain in-passed key\n";
      return false;
   }

   template < typename L, typename R > 
   bool AftrBimap< L, R >::removeUsingRightKey( const R& rightKey )
   {
      //Get iterator to right map
      typename std::map< R, L >::iterator rit = this->right.find( rightKey );
      if( rit != this->right.end() )
      {
         //Get iterator to left map
         typename std::map< L, R >::iterator lit = this->left.find( rit->second );
         if( lit != this->left.end() )
         {
            //std::cout << "Found bidirectional mapping... Removing using right key...\n";
            this->right.erase( rit );
            this->left.erase( lit );
            return true;
         }
         else
            std::cout << "Failed to removeUsingRightKey...\n"
                      << "   Left map does not contain key corresponding to right-map data\n";
      }
      else
         std::cout << "Failed to removeUsingRightKey...\n"
                   << "   Right map does not contain in passed key\n";
      return false;
   }

   template < typename L, typename R > 
   typename std::map< L, R >::iterator AftrBimap<  L,  R >::findUsingLeftKey( const L& leftKey )
   {
      return this->left.find( leftKey );
   }

   template < typename L, typename R > 
   typename std::map< R, L >::iterator AftrBimap< L, R >::findUsingRightKey( const R& rightKey )
   {
      return  this->right.find( rightKey );
   }

   template < typename L, typename R > 
   typename std::map< L, R >::iterator AftrBimap< L, R >::endIteratorLeft()
   {
      return this->left.end();
   }

   template < typename L, typename R > 
   typename std::map< R, L >::iterator AftrBimap< L, R >::endIteratorRight()
   {
      return this->right.end();
   }

   template < typename L, typename R > 
   AftrBimap< L, R >& AftrBimap< L, R >::operator =( const AftrBimap<  L,  R >& m )
   {
      if( this != &m )
      {
         this->left.clear();
         this->right.clear();
         this->left = m.left;
         this->right = m.right;
      }
      return *this;
   }

} //namespace Aftr
