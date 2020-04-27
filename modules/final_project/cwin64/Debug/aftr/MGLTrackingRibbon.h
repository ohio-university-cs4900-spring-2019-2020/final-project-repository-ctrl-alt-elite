#pragma once

#include <vector>
#include "MGL.h"

namespace Aftr
{

class TrackInfo
{
public:
   TrackInfo(){}
   TrackInfo(const Vector& trackPoint, const Vector& plumbPoint, float roll);
   Vector trackPoint;
   Vector plumbPoint;
   float roll;
};

class MGLTrackingRibbon : public MGL
{
public:
   static MGLTrackingRibbon* New(WO* parent);
   virtual ~MGLTrackingRibbon();
   void addTrackPoint(const TrackInfo& p);
   void addTrackPoint(const TrackInfo& p, Aftr::aftrColor4ub color );
   virtual void render( const Camera& cam );
   virtual void render32(const Camera& cam);
   virtual void render21(const Camera& cam);
   void setCompletePercentage(float x){completePercentage = x;}
   std::vector<TrackInfo>& getTrackPoints() { return trackPoints; }
   void setXYScale(float x) { XYScale = x; }
   float getXYScale() { return XYScale; }
   float getZScale() { return ZScale; }
   Vector getOffset() { return offset; }
   void setZScale(float x) { ZScale = x; }
   void setOffset(Vector x) { offset = x; }
   void setPlumblineRatio(unsigned int x) { plumblineRatio = x; }
   unsigned int getPlumblineRatio() const { return this->plumblineRatio; }
   void setRibbonLength(float x) { ribbonLength = x; }
   void setColor(const Vector& x);
   void clear();

   void recalcIndexedGeometry();
   bool recalculateAfterAddition() { return recalcAfterAddition; }
   void recalculateAfterAddition(bool x) { recalcAfterAddition = x; }

   float getCompletionPercentage() { return completePercentage; }
   void calcNewestPoint();
protected:
   MGLTrackingRibbon(WO* parent);
   void calculateYsAndZs(std::vector<Vector>& ys, std::vector<Vector>& zs);
   void createRibbonVertices(std::vector<Vector>& ys);
   void createRibbonIndices();
   void createRibbonNormals(std::vector<Vector>& zs);
   void createRibbonColors();
   //void createRibbonTextureCoords();

   void createPlumbVertices();
   void createPlumbIndices();
   void createPlumbColors();

   void calculateYAndZ(std::vector<Vector>& y, std::vector<Vector>& z);
   void addRibbonVertices(std::vector<Vector>& y);
   void addRibbonIndices();
   void addRibbonNormals(std::vector<Vector>& z);
   void addRibbonColors();
   //void createRibbonTextureCoords();

   void addPlumbVertices();
   void addPlumbIndices();
   void addPlumbColors();

   std::vector<TrackInfo> trackPoints;
   std::vector<aftrColor4ub> trackColors;
   float completePercentage;
   float XYScale;
   float ZScale;
   Vector offset;

   WO* parent;
   unsigned int plumblineRatio;
   float ribbonLength;
   Vector color;

   bool recalcAfterAddition;

   //indexed geometry components
   //Ribbon
   GLuint* ribbonIndices;
   GLfloat* ribbonVertices;
   GLfloat* ribbonNormals;
   GLfloat* ribbonTextureCoords;
   GLubyte* ribbonColors;
   //Plumb Lines
   GLuint* plumbIndices;
   GLfloat* plumbVertices;
   GLubyte* plumbColors;

   size_t currentSize;
   void resize();
};

}

