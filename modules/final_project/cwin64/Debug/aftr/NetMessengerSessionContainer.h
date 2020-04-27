#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <vector>
#include <boost/thread.hpp>

namespace Aftr
{

class NetMessengerServerSession;

class NetMessengerSessionContainer
{
public:
   NetMessengerSessionContainer();
   virtual ~NetMessengerSessionContainer();

   void lock();
   void unlock();

   /// Returns a reference to the internal std::vector.
   /// Ensure the user invokes lock prior to this and unlock
   /// when done using this vector. This method will be 
   /// removed shortly and replaced with wrappers.
   std::vector< NetMessengerServerSession* >& getSessions();

protected:

   boost::mutex mutex; ///< Used internally to lock access to this container in a thread safe manner
   std::vector< NetMessengerServerSession* > sessions;
};

} //namespace Aftr

#endif
