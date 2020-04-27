#pragma once

#include <map>
#include <string>
#include <vector>

/**

This is the Environment Configuration Manager.

It allows the user to define environment variables it may wish to use later
in the simulation, and store them in a globally accessible location.

Certain variable names are reserved/expected and have additional functionality.
For instance, there are getWindowHeight and getWindowWidth function, because
these variables will always exist.

Some values do have defaults, but there is no sanity checking.

If you assign a screen width of 1, that is probably not what you want, but it
should work.

*/

namespace Aftr
{

class ManagerEnvironmentConfiguration
{
public:
   ///accessors for variables that always exist

   /// Minimum milliseconds spent processing each frame. If the frame completes prior to this limit,
   /// the main thread sleeps until reaching this limit. The default is 16ms, which is ~62.5 frames per second
   /// 1000ms / 60 frames = 16.67ms / frame.
   static unsigned int getMinMilliSecondPerFrame();
   static int getWindowWidth();
   static int getWindowHeight();
   static bool isFullscreen();
   static unsigned int getGLRequestedMajorVersion(); ///< Returns the GL Version requested within the conf file
   static unsigned int getGLRequestedMinorVersion(); ///< Returns the GL Version requested within the conf file
   static void getGLRequestedVersion( unsigned int& outMajGLVersion, unsigned int& outMinGLVersion); ///< Returns the GL Version requested within the conf file
   static bool isGLRequestedContextProfileCompatibility(); ///< Returns if the conf file requested an OpenGL Compatibility Profile
   static bool isGLRequestedContextProfileCore(); ///< Returns if the conf file requested an OpenGL Core Profile
   static bool isGLRequestedContextProfileES(); ///< Returns if the conf file requested an OpenGL ES Profile
   static bool isGLDebugMessageCallbackEnabled(); ///< Returns true if glDebugMessageCallbackIsEnabled is not 0 or false; true otherwise.

   /// Returns the shared multi-media path set in the environment
   static std::string getSMM();
   /// Returns the local multi-media path set in the environment
   static std::string getLMM();
   /// Returns the path to the usr's GNUPlot Binary (for windows)
   static std::string getGNUPlotBin();
   
   /// register a new variable
   static void registerVariable( const std::string& key, const std::string& value);
   
   /// returns the variable corresponding to the given key if it exists otherwise returns an empty string
   static std::string getVariableValue( const std::string& key);
   /// returns true if key exists in the Environment; false, otherwise.
   static bool existsVariableValue( const std::string& key );

   /// Adds all the variables in a file to the environment
   static void populateFromFile( const std::string& filename = "../aftr.conf" );
   static void populateFromFileUsingAdditionalSearchDirectories( const std::string& filename, const std::vector< std::string >& additionalSearchDirectories );
   static void populateFromCommandLineArguments( const std::vector< std::string >& args );
   static void populateToFile( const std::string& filename );
   static std::string toString();
   static void deleteEnvironmentConfiguration();///<psuedo-destructor
   static void init();
protected:
   static std::string processVariable( const std::string& variable);
   static std::map<std::string,std::string>* environmentConfiguration;
};

}

