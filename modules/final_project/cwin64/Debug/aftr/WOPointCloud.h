#pragma once

#include "WO.h"
#include "AftrOpenGLIncludes.h"

namespace Aftr
{
class WOPointCloud : public WO
{
public:
   static WOPointCloud* New( Camera** cam, bool useColors = false, bool useNormals = false, bool useTexCoords = false );
   virtual ~WOPointCloud();   
   void setPoints( const std::vector<Vector>& pts );
   void setColors( const std::vector<aftrColor4ub>& colors );
protected:
   WOPointCloud();
   virtual void WOPointCloud::onCreate( Camera** cam, bool useColors, bool useNormals, bool useTexCoords );
};

}
