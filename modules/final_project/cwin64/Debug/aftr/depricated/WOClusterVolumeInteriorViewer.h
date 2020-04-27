#pragma once

#include "WO.h"

namespace Aftr
{

/** 
   \class WOClusterVolumeInteriorViewer
   \author Scott Nykl
   \brief A Fixed-position scud launcher.

   \{
*/
class WOClusterVolumeInteriorViewer : public WO
{
public:

   /**
      WOClusterVolumeInteriorViewer constructor.
      \param lxlylz The length in the X,Y, and Z directions of the WOBoundingShell.
      \param mass The mass, in kilograms, of the WOClusterVolumeInteriorViewer.
      \see WOBoundingShell
   */
   WOClusterVolumeInteriorViewer();

   /**
      Destructor of WOClusterVolumeInteriorViewer. Only directly deletes the animations; everything else is deleted
      by the implicit call to WO's destructor.
   */
   virtual ~WOClusterVolumeInteriorViewer();
   virtual void render( const Camera& cam );

   void updateInteriorClusterVolume( Vector& pos, Vector& lxlylz );


protected:

};

/** \} */

} //namespace Aftr

