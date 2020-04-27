#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include <set>
#include "NetSimulation.h"

namespace Aftr
{

class NetClusterWOCloneManager;
class NICProberServerToServer;
class ConnServerCluster;

/**
   \class NetClusterWOCloneSession
   \author Scott Nykl

   Each instance of this class represents a single WO that resides on a cluster server. The 
   corresponding WO of this object is located in a border zone within the server cluster 
   volume in which it resides. Because it is in a border zone, neighboring server clusters
   adjacent to that border zone must be informed about this WO's behavior since it is
   possible that this WO will soon leave its current local server cluster volume and need to be
   handed off to a neighboring server cluster.

   This class represents ONE WO being cloned to/from ONE server. If this WO is in the corner of
   a border shared by 7 neighboring servers, then seven instances of this class shall exist; one
   instance syncing this WO to one neighboring server.
   \{
*/
class NetClusterWOCloneSession
{
public:
   NetClusterWOCloneSession( NetClusterWOCloneManager* cloneManager, 
                             unsigned int neighborServerID,
                             NICProberServerToServer** neighbors );
   virtual ~NetClusterWOCloneSession();

   /**
      Invoked by NetClusterWOCloneManager each 'tick' to allow this session to propagate all
      new relevant information to interested neighbors.
   */
   void updateClusterCloneSession( NetSimulation::POS_IN_CLUSTER_VOLUME pos, std::set< unsigned int >& neighborServerIDs );
   
   /**
      Resets this session to its initial state before any session was established.
   */
   void resetCloneSessionState();

   enum CLONE_STATE { NOT_CLONING = 0, CLONING };

protected:

   CLONE_STATE cloneState;

   /**
      Begins cloning a 'copy' of this WO on a neighboring server. This cloning occurs when this WO comes near to that 
      neighboring server's volume. This way, once an official handoff occurs, no ODE interpentration will exist that
      could cause objects to 'explode' or fly apart in unnatural or unexpected ways.
   */
   void startCloneSession( ConnServerCluster* conn );

   /**
      Terminates a clone of this WO on a neighboring server. This is typically invoked when that WO leaves the 
      border zone; ie, either enters back into this server cluster's interior or is handed off. When this WO is handed off
      all clone sessions are destroyed prior to the handoff occurring.
   */
   void terminateCloneSession( ConnServerCluster* conn );

   /**
      This method is invoked each tick to foward all keyboard key presses to the clones residing on neighboring servers.
      This way, objects such as cars/helicopters that have user controlled state remain consistant across clones.
   */
   void updateCloneSession( ConnServerCluster* conn );

   NetClusterWOCloneManager* cloneManager; ///< Parent manager that ownes and updates this clone session
   unsigned int neighborServerID; ///< ID of the neighboring server this session communicates with
   NICProberServerToServer** neighbors; ///< Pointer to the NetSimulation's array of neighboring server cluster interfaces

   /**
      True if this WO is in neighborServerIDs set during the last iteration, that is,
      the iteration prior to this one.
   */
   bool notifiedNeighborDuringLastTick;

   /**
      This value is the number of milliseconds between periodic forced updates
      of authoritative WOs that are currently being cloned to neighboring servers.
      For this force synchronization to occur, the clone session of this particular
      WO must have been active for at least the number of milliseconds specified below.

      For example, if this value is set to 10 seconds (unrealistically large value);
      this NetClusterWOCloneSession must be active for 10 seconds before the force
      sync is sent to the respective neighboring server.
   */
   static const unsigned int CLONE_SESSION_FORCE_SYNC_WATCHDOG_THRESHOLD = 500; //half second
   
   /**
      Enables the Clone Session Watch Dog Force synchronization if set to true; otherwise
      the force sync'ing is perminantely disabled.
   */
   static const bool CLONE_SESSION_FORCE_SYNC_WATCHDOG_ENABLED = false;

   /**
      This is the internal counter which stores how much time has elapsed
      since the last force sync. This sync's position, orientation, linear 
      velocity, and angular velocity.
   */
   unsigned int cloneSessionUpdateWatchDogTimer;
};

/**
   \}
*/

} //namespace Aftr

#endif //AFTR_CONFIG_USE_TNL
