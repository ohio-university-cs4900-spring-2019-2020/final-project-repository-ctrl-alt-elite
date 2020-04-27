#pragma once

#include "WO.h"
#include "Vector.h"
#include "MGLRay.h"

namespace Aftr
{

class WORay : public WO
{
public:
   friend class MGLRay;
   static WORay* New( const Vector& rayHead, const Vector& rayTail );
   virtual ~WORay();
   void setRayHead( const Vector& rayHead );
   void setRayTail( const Vector& rayTail );
   void setRayHeadAndTail( const Vector& rayHead, const Vector& rayTail );
   Vector getRayHead() const { return this->rayHead; }
   Vector getRayTail() const { return this->rayTail; }
   void getRayHeadAndTail( Vector& rayHead, Vector& rayTail ) const { rayHead = this->rayHead; rayTail = this->rayTail; }
protected:
   virtual void onCreate();
   WORay( const Vector& rayHead, const Vector& rayTail );

   Vector rayHead;
   Vector rayTail;

};


} //namespace Aftr

