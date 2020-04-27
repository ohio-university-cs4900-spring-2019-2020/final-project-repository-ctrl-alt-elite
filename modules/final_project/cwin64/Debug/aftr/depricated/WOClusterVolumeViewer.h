#pragma once

#include "WO.h"

namespace Aftr
{
   class WOClusterVolumeInteriorViewer;

/** 
   \class WOClusterVolumeViewer
   \author Scott Nykl
   
   This is a special object pertaining explicitly to cluster server operations.

   A WOClusterVolumeViewer draws the exterior and interior zones of the volume of space
   managed by a single server cluster. This object is required to be placed into 
   GLView::worldLst by the user if he will ever use his module on a set of cluster servers.

   Every Cluster Server MUST have EXACTLY ONE WOClusterVolumeViewer; this object is used
   as the scope object for clients that are not current a resident of this cluster server's
   volume. The user is required to instantiate exactly one of these objects within his
   module's GLView::LoadMap().

   For example:
   GLViewMyModule::LoadMap()
   {
      ...
      wo = new WOClusterVolumeViewer();
      wo->setLabel( "WOClusterVolumeViewer\0" );
      worldLst->push_back( wo );
      ...
   }

   This is all that is needed to make a module work within a server cluster environment.

   \{
*/
class WOClusterVolumeViewer : public WO
{
public:

   /**
      WOClusterVolumeViewer constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOClusterVolumeViewer.
      \see WOBoundingShell
   */
   WOClusterVolumeViewer();

   /**
      Destructor of WOClusterVolumeViewer. Only directly deletes the animations; everything else is deleted
      by the implicit call to WO's destructor.
   */
   virtual ~WOClusterVolumeViewer();

   virtual void render( const Camera& cam );

   virtual void onKeyDown( const SDL_KeyboardEvent& key );

	virtual void onKeyUp( const SDL_KeyboardEvent& key );

   void updateClusterVolume( Vector& pos, Vector& lxlylz, Vector& interiorLxLyLz );


protected:

   WOClusterVolumeInteriorViewer* interiorBorder;

};

/** \} */

} //namespace Aftr

