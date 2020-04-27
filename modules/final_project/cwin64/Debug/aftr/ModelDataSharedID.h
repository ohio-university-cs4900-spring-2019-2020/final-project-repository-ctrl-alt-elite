#pragma once

#include "Vector.h"
#include <string>

namespace Aftr
{

class ModelDataSharedID
{
public:
   ModelDataSharedID();
   ModelDataSharedID( const ModelDataSharedID& toCopy );
   ModelDataSharedID( const std::string& fileName, const Vector& scale );
   virtual ~ModelDataSharedID();
   ModelDataSharedID& operator =( const ModelDataSharedID& id );
   bool operator ==( const ModelDataSharedID& id ) const;
   bool operator < ( const ModelDataSharedID& id ) const;
   std::string toString() const;
   std::string getFileName() { return this->fileName; }
   Vector getScaleFactor() { return this->scale; }
   unsigned int getInstanceCount() const { return this->instanceCount; }
   void incrementInstanceCount() { ++this->instanceCount; }
   void decrementInstanceCount() { --this->instanceCount; }
protected:
   std::string fileName;
   Vector scale;
   unsigned int instanceCount;
};

} //namespace Aftr

