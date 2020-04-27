#pragma once

#include "AftrConfig.h"
#include "AftrOpenGLIncludes.h"

namespace Aftr
{

struct VertexListEntryGL_V2F
{
   GLfloat x,y;
};

struct VertexListEntryGL_V3F
{
   GLfloat x,y,z;
};

struct VertexListEntryGL_C4UB_V3F
{
   GLubyte r,g,b,a;
   GLfloat x,y,z;
};

struct VertexListEntryGL_C3F_V3F
{
   GLfloat r,g,b;
   GLfloat x,y,z;
};

struct VertexListEntryGL_N3F_V3F
{
   GLfloat nx, ny, nz;
   GLfloat x,y,z;
};

struct VertexListEntryGL_C4F_N3F_V3F
{
   GLfloat r,g,b,a;
   GLfloat nx, ny, nz;
   GLfloat x,y,z;
};

struct VertexListEntryGL_T2F_V3F
{
   GLfloat u,v;
   GLfloat x,y,z;
};

struct VertexListEntryGL_T4F_V4F
{
   GLfloat s,t,u,v;
   GLfloat x,y,z,w;
};

struct VertexListEntryGL_T2F_C4UB_V3F
{
   GLfloat u,v;
   GLubyte r,g,b,a;
   GLfloat x,y,z;
};

struct VertexListEntryGL_T2F_C3F_V3F
{
   GLfloat u,v;
   GLfloat r,g,b;
   GLfloat x,y,z;
};

struct VertexListEntryGL_T2F_N3F_V3F
{
   GLfloat u,v;
   GLfloat nx, ny, nz;
   GLfloat x, y, z;
};

struct VertexListEntryGL_T2F_C4F_N3F_V3F
{
   GLfloat u,v;
   GLfloat r,g,b,a;
   GLfloat nx, ny, nz;
   GLfloat x,y,z;
};

struct VertexListEntryGL_T4F_C4F_N3F_V4F
{
   GLfloat s,t,u,v;
   GLfloat r,g,b,a;
   GLfloat nx, ny, nz;
   GLfloat x,y,z,w;
};

struct VertexListEntry_Tangents
{
   GLfloat u, v;       ///< Texture coordinate

#ifdef AFTR_CONFIG_COLOR_UNSIGNED_BYTE
   GLubyte r, g, b, a; ///< color
#endif

   GLfloat nx, ny, nz; ///< normal vector
   GLfloat x, y, z;    ///< position vector
   GLfloat tx, ty, tz; ///< tangent vectors
};

struct VertexListEntry
{
   GLfloat u, v;       ///< Texture coordinate
#ifdef AFTR_CONFIG_COLOR_FLOAT
   GLfloat r, g, b, a;
#endif

#ifdef AFTR_CONFIG_COLOR_UNSIGNED_BYTE
   GLubyte r,g,b,a;    ///< color
#endif

   GLfloat nx, ny, nz;///< normal vector
   GLfloat x, y, z;   ///< position vector
};

}

