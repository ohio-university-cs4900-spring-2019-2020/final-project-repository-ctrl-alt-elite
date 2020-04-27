//----------------------------------------------------------------------------
//Description: The TextureVertex class stores the 2 Dimensional points that
//map a Texture on to the surface of a ModelShape. The origin of reference for
//these 2D points is the lower left corner of the ModelShape.  OpenGL uses
//these to neatly paint a texture over a surface.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include <string>

//----------------------------------------------------------------------------
//Description: The TextureVertex class stores the 2 Dimensional points that
//map a Texture on to the surface of a ModelShape. The origin of reference for
//these 2D points is the lower left corner of the ModelShape.  OpenGL uses
//these to neatly paint a texture over a surface.
//----------------------------------------------------------------------------
namespace Aftr
{

class TextureVertex
{
public:
   //default constructor
   TextureVertex();

   //-------------------------------------------------------------------------
   //Constructor that instantiates a new TextureVertex.
   //string s: string containing a 2 dimensional point indicating where
   //the texture will be drawn.
   //-------------------------------------------------------------------------
   TextureVertex( const std::string& s );

   //-------------------------------------------------------------------------
   //Destructor that deletes and NULL-ifys all pointers owned by this 
   //instance.
   //-------------------------------------------------------------------------
   virtual ~TextureVertex();

   ///== operator
   bool operator==(const TextureVertex& tv)const;

   ///!= operator
   bool operator!=(const TextureVertex& tv)const;

   ///less than operator
   bool operator<(const TextureVertex& tv)const;

   float x;   //The current X coordinate of the textureVertex
   float y;   //The current Y coordinate of the textureVertex
};
} //namespace Aftr
