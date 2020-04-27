#pragma once

#include "MGLPointSet.h"

namespace Aftr
{

class WOPointSetRandom;
class ParticleDataPointSprite;

class MGLPointSetRandom : public MGLPointSet
{
public:
   MGLPointSetRandom( Camera** camPtr, WOPointSetRandom* parent );
   virtual ~MGLPointSetRandom();
   virtual void populatePointSet();
   virtual void copyModelPointSet( MGLPointSetRandom* source );

protected:


   WOPointSetRandom* p = nullptr; ///< Parent WO of this MGLPointSetRandom

};

} //namespace Aftr

