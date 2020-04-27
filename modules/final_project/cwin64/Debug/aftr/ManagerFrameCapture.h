#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Aftr
{

class AftrFrameCapture;
class Texture;

class ManagerFrameCapture
{
public:
   static void init();
   static void shutdown();
   static void onWindowResize(); ///< Called by ManagerWindowing to inform this manager about window size changes

   static std::unique_ptr<AftrFrameCapture> captureTexture( const Texture* tex );
   static std::unique_ptr<AftrFrameCapture> captureFrame();
   ///Returns the index of this captured frame in the internal buffer of ManagerFrameCapture
   static size_t captureFrameToBuffer();
   static size_t captureTextureToBuffer( const Texture* tex, const std::string& fileName = "" );
   static bool captureFrameToFile( const std::string& fileName = "", bool removeFromBufferAfterWritingToDisk = true, unsigned int* outBufferIndex = NULL );

   /**
      Returns the Captured Frame at the specified index. If index is invalid, NULL is returned.
      The returned Frame is OWNED by this manager, the user should NOT delete the pointer directly.
      To free this frame, invoke clearBuffer() (which clears all frames) or invoke
      clearBufferAtIndex( size_t i ).
   */
   static AftrFrameCapture* getFrameFromBufferAtIndex( size_t index );
   static bool clearBufferAtIndex( size_t i );
   static size_t getNumFramesInBuffer();

   static void clearBuffer();
   static size_t writeAllBufferedFramesToFile( bool removeFromBufferAfterWritingToDisk = true );
   static bool writeFrameAtIndexToFile( size_t index, const std::string& fileName, bool removeFromBufferAfterWritingToDisk = true );

   static bool captureTextureToFile( const Texture* tex, const std::string& fileName = "" );

   static std::string getNextCandidateFrameCaptureFileName();

   static void capturePanorama();

   //performance test, can remove later - returns average number of seconds to capture panorama frames (without writing to disk)
   static unsigned int performancePanorama();

protected:

   static std::vector< std::unique_ptr<AftrFrameCapture> >* buffer; ///< stores all captured frames that haven't been flushed
   static char* flipBuffer; ///< Buffer used to flip the screen capture upright, resized on Window resize

};


} //namespace Aftr


