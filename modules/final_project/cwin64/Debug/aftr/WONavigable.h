#pragma once

#include "WO.h"

namespace Aftr
{

class WONavigable : public WO
{
public:
   static WONavigable* New( const std::string& modelFileName, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstSMOOTH );

   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );
   virtual void onMouseDown( const SDL_MouseButtonEvent& mouse );
   virtual void onMouseUp( const SDL_MouseButtonEvent& mouse );
   virtual void onMouseMove( const SDL_MouseMotionEvent& mouse );

protected:
   WONavigable();
   virtual ~WONavigable();

   float stepSize;
   float rotStepSizeInDeg;

};


} //namespace Aftr
