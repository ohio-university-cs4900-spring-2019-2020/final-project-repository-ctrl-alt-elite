#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <queue>
#include <boost/thread.hpp>

namespace Aftr
{

class NetMsg;

template< typename T >
class NetMessengerMessageQueueT
{
public:

   using value_type =  T;

   NetMessengerMessageQueueT();
   virtual ~NetMessengerMessageQueueT();

   void lock();
   void unlock();

   /// Returns a reference to the internal std::queue.
   /// Ensure the user invokes lock prior to this and unlock
   /// when done using this queue. This method will be 
   /// removed shortly and replaced with wrappers.
   std::queue< T >& getQueue();

protected:

   boost::mutex mutex; ///< Used internally to lock access to this container in a thread safe manner
   std::queue< T > msgQueue;
};

//Insert these aliases in the namespace
using NetMessengerMessageQueue = NetMessengerMessageQueueT< NetMsg* >;

} //namespace Aftr

#include "NetMessengerMessageQueue.cpptemplate.h"

#endif
