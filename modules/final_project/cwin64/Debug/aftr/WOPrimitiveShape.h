#pragma once

#include <string>
#include "WO.h"

namespace Aftr
{
   enum class PRIMITIVE_SHAPE_TYPE; //defined in MGLPrimitiveShape.h
   
   /**
      \author Chad Mourning and Scott Nykl
   */


   class WOPrimitiveShape : public WO
   {
   public:
      static WOPrimitiveShape* New( PRIMITIVE_SHAPE_TYPE type, const std::vector<float>& parameters );
      static WOPrimitiveShape* New( const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors );
      virtual ~WOPrimitiveShape();
   protected:
      virtual void onCreate( PRIMITIVE_SHAPE_TYPE type, const std::vector<float>& parameters );
      virtual void onCreate( const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors );
      WOPrimitiveShape();
   private:
   };
}

