//----------------------------------------------------------------------------
//!Description: The WOBoundingShell class
//
//!Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"

//----------------------------------------------------------------------------
//Description: The WOBoundingShell class 
//----------------------------------------------------------------------------


namespace Aftr
{

/** \class WOBoundingShell
    \brief An inheritable class used for 

    \{
*/
class WOBoundingShell : public WOODE
{

public:
   static WOBoundingShell* New( const Vector& lxlylz, float mass );
   virtual ~WOBoundingShell();


protected:
   WOBoundingShell();
   virtual void onCreate( const Vector& lxlylz, float mass );

   Vector lxlylz;


};

/** \} */

} //namespace Aftr



#endif
