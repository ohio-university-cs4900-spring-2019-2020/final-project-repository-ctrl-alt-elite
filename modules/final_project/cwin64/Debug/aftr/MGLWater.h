#pragma once

#include "MGLGridSelfDividing.h"
#include "Wave.h"

namespace Aftr
{

   class GLView;

   class MGLWater : public MGLGridSelfDividing
   {
   public:
      MGLWater( WO* parentWO, GLView* view,///parent view class
         int x,///x-length of grid
         int y,///y-height of grid
         int z,///z-length
         float t,///height perterb threshhold
         int n,///fidelity (~rows)
         int s,///number of display list states used
         int u,///update timer
         int r,///# of instances
         int c,
         Wave b,
         float min,
         float max,
         float v,
         int lod
         );	
      virtual ~MGLWater();   
      virtual void initOpenGL();  
      virtual void render( const Camera& cam );
      virtual void renderSelection( GLubyte red, GLubyte green, GLubyte blue ){};
      int getUpdateTimer(){return updateTimer;}
      void phaseShift(float x);
      bool getDynamic(){return dynamic;}
      int getLength(){return length;}
      int getWidth(){return width;}
      int getLOD(){return lod;}
      void setLOD(int x){lod = x;}
      size_t getDescriptionSize(){return sizeD;}
      Wave getBehavior(){return behavior;}
      float getMinPhase(){return minPhase;}
      float getMaxPhase(){return maxPhase;}
      void updateWorld(unsigned int x);
      GLView* glview;
      float minPhase;
      float maxPhase;
      float velocity;
      float diff;
      void addClonePosition(Aftr::VectorD relPos);
   protected:
      bool dynamic;
      void renderDynamic(int x, int y);///least efficient rendering method, used for high preformance results
      void renderBasic(int x, int y);
      void render1();
      void render2();
      void render3(int x, int y);
      void render4();
      void update();  
      void updateColor();

      int updateTimer;///timer at which the state of the grid's display list updates
      int colorTimer;
      int updateTime;
      int colorTime;
      Wave behavior;
      int instances;

   private:
      int length;
      int width;
      int lod;
      int numRows;
      int numCols;
      std::vector<VectorD> clones;

   };


}  //namespace Aftr


