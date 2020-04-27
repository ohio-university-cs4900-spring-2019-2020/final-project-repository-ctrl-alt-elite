#pragma once
#include <memory>
#include <string>
#include <unordered_map>
//Written by Scott Nykl. Managers the FreeType Fonts that are rendered based on Signed Distance Maps
//(Contour maps) of the fonts. Enabling higher quality fonts. These are also rendered via VAO'd buffers
//improving performance.

namespace Aftr
{

   class FTGLFontDataShared;

class ManagerFTGLFont
{
public:
   static void init();
   static void shutdown();
   static std::shared_ptr< FTGLFontDataShared >loadFTGLFont( const std::string& fileName, float fontSize, size_t atlasSizePixelsSq = 512 );
   static std::shared_ptr< FTGLFontDataShared >loadFTGLFont( const std::string& fileName, float fontSize, const std::wstring& charsToLoad, size_t atlasSizePixelsSq );

   /// Returns the key used to hash this shared data. The fontSize truncates to 2 decimal places of precision (17.127 and 17.121 both reduce to 17.12), so only
   /// One font of name,17.12*,size may exist at any time.
   static std::string getHashKey( const std::string& fileName, float fontSize, size_t atlasSizePixelsSq );
protected:
   static std::unordered_map< std::string, std::shared_ptr<FTGLFontDataShared> >* cache;
   static bool HasBeenInitialized;
};

}

