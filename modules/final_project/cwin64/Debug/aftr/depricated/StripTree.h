#pragma once

#include <vector>
#include "Vector.h"

namespace Aftr
{

enum StripOrientation { soXZ, soYZ, soMAX_ORIENTATIONS };

class StripTreeNode
{
public:
   StripTreeNode( std::vector< Vector* >& points, StripOrientation orientation, Vector endPoint1, Vector endPoint2 );
   std::pair< StripTreeNode*, StripTreeNode* > split();
   double getError() { return error; }
   Vector getEndPoint1() { return endPoint1; }
   Vector getEndPoint2() { return endPoint2; }
   double getLowerWidth() { return lowerWidth; }
   double getUpperWidth() { return upperWidth; }
   Vector getNormal() { return normal; }
protected:
   Vector endPoint1;
   Vector endPoint2;
   double upperWidth;
   double lowerWidth;
   double error;//area of the rectangles

   Vector normal;

   std::vector< Vector* > points;
   StripOrientation orientation;

   void findWidthsAndErrors();
   Vector calcNormal();//based on orientation
};

class StripTree
{
public:
   StripTree( std::vector< Vector* >& points, StripOrientation orientation, int levelsToGenerate ); 
   void render( unsigned int levelToRender );
   virtual ~StripTree();
   std::vector< std::vector< StripTreeNode* > >& getLevels() { return levels; }
protected:
   std::vector< Vector* > points;
   std::vector< std::vector< StripTreeNode* > > levels;
   StripOrientation orientation;
   void generate( int levelsToGenerate );
   std::vector< Vector* > orient_sort( std::vector< Vector* > points );//pass a copy to be manipulated, could use a move constructor return type

};

}

