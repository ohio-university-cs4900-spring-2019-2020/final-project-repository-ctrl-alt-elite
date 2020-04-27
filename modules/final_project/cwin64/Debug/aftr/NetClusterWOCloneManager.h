#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include <vector>
#include <set>
#include "NetSimulation.h"

struct SDL_KeyboardEvent;

namespace Aftr
{

class WO;
class NICProberServerToServer;
class NetClusterWOCloneSession;

/**
   \class NetClusterWOCloneManager
   \author Scott Nykl

   Each WO instance within a server cluster has one of these objects. This object is responsible
   for ensuring that the corresponding WO's state is properly replicated to neighboring servers.
   State is replicated to neighboring servers ONLY when this WO is within the BORDER zones of the
   local server cluster's volume.

   Once the WO is initially replicated to a neighboring server, the corresponding ODE bodies, geoms,
   joints, etc are initialized on the remote server; hence, only user input events need to be forwarded
   after initial replication.

   By doing this, significant amount of bandwidth and CPU overhead are saved. Continually destroying
   and recreating the entire WO on a remote server would require significant
   amounts of CPU time as well as bandwidth to send ALL relevant parameters every tick.
   \{
*/

class NetClusterWOCloneManager
{
public:
   NetClusterWOCloneManager( WO* parentWO, NICProberServerToServer** listOfNeighbors );
   virtual ~NetClusterWOCloneManager();

   void updateClusterWOCloneManager( NetSimulation::POS_IN_CLUSTER_VOLUME pos ,std::set< unsigned int >& neighboringServerIDs );

   bool canPerformHandOffOnThisWO() { return this->CanPerformHandOffOnThisWO; }
   void canPerformHandOffOnThisWO( bool canHandOff ) { this->CanPerformHandOffOnThisWO = canHandOff; }

   /**
      Returns true if the corresponding WO currently resides in this local server cluster's volume; false,
      otherwise.
   */
   bool isAuthoritative() { return this->IsAuthoritative; }

   /**
      Sets whether or not the corresponding WO is Authoritative; i.e., the WO currently resides
      in this local server cluster's volume (true), or not (false). This method is set automatically
      by NetSimulation and should not be invoked by a User.
   */
   void isAuthoritative( bool isAuthoritative ) { this->IsAuthoritative = isAuthoritative; }

   /**
      Resets the state of all NetClusterCloneSession objects managed by this object. This also
      resets the internal state of this manager; for example, it clears out all keyboard key presses
      residing within any of the key pressed/key released sets.
   */
   void resetWOCloneManagerState();

   /**
      \returns a pointer to the WO this manager is responsible for.
   */
   WO* getParentWO() { return this->parentWO; }

   void onKeyDown( const SDL_KeyboardEvent& key );
   void onKeyUp( const SDL_KeyboardEvent& key );

   /**
      \returns a reference to the current keys that are pressed. \see currentKeysPressed.
   */
   std::set< SDLKey >& getCurrentKeysPressed() { return this->currentKeysPressed; }

   /**
      \returns a reference to the keys that were pressed within the last tick. \see recentKeysPressed.
   */
   std::set< SDLKey >& getRecentKeysPressed() { return this->recentKeysPressed; }

   /**
      \returns a reference to the keys that were released within the last tick. \see recentKeysReleased.
   */
   std::set< SDLKey >& getRecentKeysReleased() { return this->recentKeysReleased; }

protected:

   bool CanPerformHandOffOnThisWO; ///< True if this can be handed off between server clusters
   bool IsAuthoritative; ///< True if the corresponding WO resides within this local server cluster's volume

   NICProberServerToServer** neighbors; ///< Pointer to the NetSimulation's array of neighboring server cluster interfaces

   std::vector< NetClusterWOCloneSession* > cloneSessions; ///< Vector of pointers to all NetClusterCloneSessions managed by this object

   WO* parentWO; ///< Parent WO that is managed by this NetClusterWOCloneManager

   //need to store all key data about this WO
   //
   std::set< SDLKey > currentKeysPressed; ///< keys that have been down and are waiting to be release
   std::set< SDLKey > recentKeysPressed; ///< keys that have JUST been pressed. On the next tick, these keys will be moved to currentKeysPressed
   std::set< SDLKey > recentKeysReleased; ///< keys that have JUST been released. On the next tick, the corresponding key in currentKeysPressed will be removed

};

/**
   \}
*/

} //namespace Aftr

#endif //AFTR_CONFIG_USE_TNL
