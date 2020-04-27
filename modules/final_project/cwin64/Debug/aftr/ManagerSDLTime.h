//----------------------------------------------------------------------------
//Description: The ManagerSDLTime class...
//
//Author: Scott Nykl & Chad Mourning
//----------------------------------------------------------------------------

#pragma once

#include <vector>
#include <map>

namespace Aftr
{
   class WO;

#ifdef TIME_DIAGNOSTIC

/**

The TimeShare class is only used for time diagnostic operations.  It is not compiled in if time diagnostic is not being used.

*/

class TimeShare
{
public:
   ///default constructor, 0s out all member variables
   TimeShare();
   ///sum total time spent in Render for this WO
   unsigned int timeSpentInRender;
   ///sum total time spent in RenderSelection for this WO
   unsigned int timeSpentInRenderSelection;
   ///sum total time spent in onPhysicsEngineTick for this WO
   unsigned int timeSpentInGLUpdate;
   ///sum total time spent in ODEUpdateForcesAndJoints for this WO
   unsigned int timeSpentInUpdateFAJ;
   ///sum total time spent in ODEUpdatePositionAndOrientation for this WO
   unsigned int timeSpentInUpdatePAO;
   ///sum total time spent onUpdateWO
   unsigned int timeSpentInOnUpdate;
   ///sum total times they enter render (used for averaging) for this WO
   unsigned int numberOfTimesInRender;
   ///sum total times they enter renderSelection (used for averaging) for this WO
   unsigned int numberOfTimesInRenderSelection;
};

#endif

class ManagerSDLTime
{
public:

   static void initialize();
   static void updateTime();
   static unsigned int getTimeSinceLastPhysicsIteration();
   static unsigned int getTimeSinceLastMainLoopIteration();
   static unsigned int getNumMainLoopIterations();
   
   ///Number of main loop iterations since the ManagerSDLTime was initialized.
   static unsigned int numMainLoops;

   #ifdef TIME_DIAGNOSTIC

   ///marks the current time in the ith slot of savedTime
   static void markTime(int i = 0);
   ///retrieves the current time in the ith slot of savedTime
   static unsigned int retrieveTime(int i = 0);
   ///prints the time diagnostic report
   static void printReport();

   ///the map between each WO and it's associated TimeShare
   static std::map<WO*,TimeShare> diagnostic;
   ///the array of marked times
   static unsigned int savedTime[NUM_TIME_MARKERS];

   ///sum total spent time preserving state this run
   static unsigned int timeSpentPreservingState;
   ///sum total time spent on worldLst->update() this run
   static unsigned int timeSpentUpdatingWorldContainer;
   ///sum total time spent printing errors this run
   static unsigned int timeSpentPrintingErrors;
   ///sum total time spent in the physics engine this run
   static unsigned int timeSpentInPhysicsEngine;
   ///sum total time spent synchronizing lights this run
   static unsigned int timeSpentSynchronizingLights;
   ///sum total time spent rendering the GUI this run
   static unsigned int timeSpentRenderingGUI;
   ///sum total time spent rendering shadows
   static unsigned int timeSpentRenderingShadows;
   ///sum total time spent rendering lens flare
   static unsigned int timeSpentRenderingLensFlare;
   ///sum total time spent flushing and swapping buffers
   static unsigned int timeSpentFlushing;

   static unsigned int timeSpentSwapping;

   static unsigned int initializedTime;

   static unsigned int timeSpentUpdatingCamera;
   static unsigned int timeSpentRenderingCamera;
   static unsigned int timeSpentRenderingAxes;

   static unsigned int timeSlept;

   static unsigned int timeSpentHandlingEvents;

   static unsigned int timeSpentInRenderLoopForAllObjects;
   static unsigned int timeSpentInUpdateWorldForAllObjects;

   #endif

   static unsigned int lastMainLoopTimeStamp;
   static unsigned int diffSinceLastMainLoopIteration;
protected:
   static unsigned int prevTimeStamp;
   static unsigned int currTimeStamp;
   static unsigned int diffSinceLastPhysicsIteration;
};

} //namespace Aftr

