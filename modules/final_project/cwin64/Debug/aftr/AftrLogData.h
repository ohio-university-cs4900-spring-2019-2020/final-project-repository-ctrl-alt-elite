#pragma once

#include "AftrLogDataMacroMethods.h"


/*************************************************************************
 SLN 22 Nov 2016: This class is deprecated and should no longer be used...
 Consider the classes AftrSensorData, AftrSensorDataFileIO, and 
 AftrSensorDataTraversal for playing back, recording, and storing log
 data.

 Getting rid of the macro infrastructure and replacing it w/ template
 meta programming and compile time expressions provide a more flexible
 path forward.

 //Need to ensure the TrimbleGPS module still works after this refactor.
  
************************************************************************/

namespace Aftr
{

class AftrLogData
{
public:
   AftrLogDataMacroDeclaration( AftrLogData );
   AftrLogData();
   virtual ~AftrLogData() = 0;
protected:
   
};


} //namespace Aftr

