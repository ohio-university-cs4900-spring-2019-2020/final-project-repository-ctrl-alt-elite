#pragma once

#include "WO.h"

namespace Aftr
{

   class WOIntersectionIndicator : public WO
   {
   public:
      static WOIntersectionIndicator* New( WO* destination, const std::vector<WO*>& intersectionList );
      virtual void onUpdateWO();
      virtual ~WOIntersectionIndicator(){};
      Vector destinationPoint;
      WO* destination;
      bool wasIntersectionLastUpdate;
      void isEnabled( bool enableIntersectionTest );
      bool isEnabled() { return this->IsEnabled; }
      std::vector< WO* >& getIntersectionList() { return this->intersectionList; }
   protected:
      virtual void onCreate();
      WOIntersectionIndicator(WO* destination, const std::vector<WO*>& intersectionList);
      std::vector<WO*> intersectionList;
      bool IsEnabled;
   };

}

