#pragma once

#include <vector>

namespace Aftr
{
   class GLView;
   class WOWayPointAbstract;
   class WO;

   enum WayPointActivationType { wpatREGULAR = 0, wpatINVERSE, wpatGLOBAL, wpatNUM_TYPES };

class WayPointParametersBase
{
public:
   WayPointParametersBase(GLView* view, std::vector<WO*> activators = std::vector<WO*>(), WayPointActivationType type = wpatREGULAR,
      float frequency = 0, bool useCamera = false, bool visible = false, bool runWhenPaused = false,
      std::vector<WOWayPointAbstract*> prereqs = std::vector<WOWayPointAbstract*>());
   GLView* view;
   float frequency;///<reset frequency in miliseconds, 0 means no reset
   bool useCamera;///<uses the glview's current camera as an activator
   bool visible;///<display activation volume?
   bool runWhenPaused;///<check for activation even if physics ticks == 0
   std::vector<WOWayPointAbstract*> prereqs;
   std::vector<WO*> activators;
   WayPointActivationType type;
};

}

