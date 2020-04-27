#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_KEYLOK_DONGLE
#include <atomic>
#include <thread>
#include <memory>
#endif

namespace Aftr
{

class ManagerKeyLok
{
public:
   static void init();
   static void shutdown();
   static bool isPolling(); ///< Returns true if polling is actively occurring - either successfully or unsuccessfully. Executed by main thread.
   static void verify(); ///< VerifiesExecuted only within main thread

protected:
#ifdef AFTR_CONFIG_USE_KEYLOK_DONGLE
   static void doPoll(); ///< Executed only within poller thread
   static bool checkForDongle();
   static short RLeft( int Target, int Counts ); ///< Used internally to rotate 

   static bool HasBeenInitialized; ///< Set to true upon initialization of manager
   static std::atomic< bool > ContinuePolling; ///< Set to false to tell polling thread to shutdown at exit.
   static std::atomic< bool > IsDongleInserted; ///< Set within polling thread. Becomes false when dongle is removed, true when inserted.
   static std::unique_ptr< std::thread > pollThread; ///< Child thread that perform polling. This thread is join'd upon shutdown of this manager.
#endif
};

} //namespace Aftr
