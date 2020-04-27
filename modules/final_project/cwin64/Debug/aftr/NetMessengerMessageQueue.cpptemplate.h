#ifdef AFTR_CONFIG_USE_BOOST
#include "NetMsg.h"


using namespace Aftr;

template< typename T >
NetMessengerMessageQueueT<T>::NetMessengerMessageQueueT()
{
}

template< typename T >
NetMessengerMessageQueueT<T>::~NetMessengerMessageQueueT()
{
   //this->lock();
   //while( !this->msgQueue.empty() )
   //{
   //   std::cout << "WARNING: Memleak in non-empty NetMessengerMessageQueueT<T>... " << AFTR_FILE_LINE_STR << "\n";
   //   //T* s = this->msgQueue.front();
   //   //delete s; s = NULL;
   //   this->msgQueue.pop();
   //}
   //this->unlock();
}

template< typename T >
void NetMessengerMessageQueueT<T>::lock()
{
   while( !this->mutex.try_lock() ) { boost::this_thread::yield(); }
}

template< typename T >
void NetMessengerMessageQueueT<T>::unlock()
{
   this->mutex.unlock();
}

template< typename T >
std::queue< T >& NetMessengerMessageQueueT<T>::getQueue()
{
   return this->msgQueue;
}

#endif
