#pragma once

#include "WO.h"
#include <vector>

namespace Aftr
{

class WOVoxelGrid : public WO
{
public:
   static WOVoxelGrid* New( const Vector& lxlylz,
                            std::vector< std::vector< std::vector< float > > >* data );
   virtual ~WOVoxelGrid();
   Vector getInitialLxlylz() { return initialLxlxly; }
protected:
   WOVoxelGrid( const Vector& lxlylz, 
                std::vector< std::vector< std::vector< float > > >* data );
   virtual void onCreate();
  
   Vector initialLxlxly;
   Vector initialNumSamples;
   std::vector< std::vector< std::vector< float > > >* data;
};

} //namespace Aftr

