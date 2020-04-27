#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <queue>
#include <boost/thread.hpp>

namespace Aftr
{

template < class T >
class AftrThreadSafeQueue
{
public:
   AftrThreadSafeQueue()
   {
   }

   virtual ~AftrThreadSafeQueue()
   {
      //this->lock();
      //while( !this->q.empty() )
      //{
      //   T s = this->q.front();
      //   delete s; s = NULL;
      //   this->q.pop();
      //}
      //this->unlock();
   }

   void clear()
   {
      this->lock();

      while( !this->q.empty() )
         this->q.pop();

      this->unlock();
   }

   void lock()
   {
      while( !this->mutex.try_lock() ) { boost::this_thread::yield(); }
   }

   void unlock()
   {
      this->mutex.unlock();
   }

   /// Returns a reference to the internal std::queue.
   /// Ensure the user invokes lock prior to this and unlock
   /// when done using this queue. This method will be 
   /// removed shortly and replaced with wrappers.
   std::queue< T >& getQueue()
   {
      return this->q;
   }

protected:

   boost::mutex mutex; ///< Used internally to lock access to this container in a thread safe manner
   std::queue< T > q;
};

} //namespace Aftr

#endif
