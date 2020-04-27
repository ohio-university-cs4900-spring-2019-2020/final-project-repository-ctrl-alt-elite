#pragma once

#include "AftrConfig.h"
#include <string>

namespace Aftr
{

class ManagerCUDA
{
public:
   static void init();
   static void shutdown();
#ifdef AFTR_CONFIG_USE_CUDA
   static std::string toStringCublasStatus(unsigned int status);
#endif
protected:
};
   
}

