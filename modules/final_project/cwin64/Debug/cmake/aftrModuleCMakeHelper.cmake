#Written by Scott Nykl as a helper module which includes common libraries included and linked by the engine
#as well as common variables used in engine build and module build makefiles.

function( MakeAbsolute path )
   list( LENGTH ${path} size )
   math( EXPR maxIdx "${size} - 1" )
   set( it 0 )
   set( myTemp )
   WHILE( it GREATER -1 AND it LESS ${size} )
      LIST( GET ${path} ${it} f )
      GET_FILENAME_COMPONENT( f ${f} ABSOLUTE )
      SET( myTemp ${myTemp} ${f} )
      MATH( EXPR it "${it}+1" )
   ENDWHILE()
   set( ${path} ${myTemp} PARENT_SCOPE )
endfunction()

#Helper which includes and defines needed libraries for New Modules to use inside their CMakeList.txt
#This file contains libraries and definitions commonly used by New Modules. It let's some common CMake
#necessities be shared among all NewModule templates. A New Module can avoid these helpers by simply
#commenting out:
#
# include( "../../../include/cmake/aftrModuleCMakeHelper.cmake" )
#
# This script is expected to be included by a CMakeLists.txts located in
# .../trunk/usr/modules/<MyModule>/src/CMakeLists.txt
#
# Below is a list of the variables that this CMake Script defines and may be used by other scripts
# which include this file:
#
# AFTR_NBITS : Either "64" or "32". If Project is set to 32 bit compilation, then this is 32. Same is true for 64 bit compilation.

MESSAGE( STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
                 "ENTERING Inside of aftrModuleCMakeHelper.cmake... Setting Up Variables..." )
                 
SET (CMAKE_VERBOSE_MAKEFILE ON )

##########
#Specify CMake Policies to avoid red warnings in the configurations as cmake's behavior changes with new versions
if( POLICY CMP0074 ) #SLN Added 14 Oct 2018
#In CMake 3.12 and above the ``find_package(<PackageName>)`` command now searches prefixes specified by the ``<PackageName>_ROOT`` CMake variable and the ``<PackageName>_ROOT`` environment variable.
   cmake_policy( SET CMP0074 NEW )
endif()
##########


#Determine if this project is a 32 bit or 64 bit project. (on *NIX -m32 indicates 32 and -m64 indicates 64).
MESSAGE( STATUS "CMAKE_SIZEOF_VOID_P is ${CMAKE_SIZEOF_VOID_P}" )
IF( ${CMAKE_SIZEOF_VOID_P} EQUAL 8 )
   SET( AFTR_NBITS "64" )
   MESSAGE( STATUS "CMAKE_SIZEOF_VOID_P EQUAL 8" )
   MESSAGE( STATUS "Project is set to Build a 64-bit binary and requires Linking against 64-bit libs." )
elseif( ${CMAKE_SIZEOF_VOID_P} EQUAL 4) 
   SET( AFTR_NBITS "32" )
   MESSAGE( STATUS "CMAKE_SIZEOF_VOID_P EQUAL 4" )
   MESSAGE( STATUS "Project is set to Build a 32-bit binary and requires Linking against 32-bit libs." )
else()
   MESSAGE( FATAL_ERROR "CMAKE_SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P}... This script expected to detect either 4 or 8 (32 bit or 64 bit)." )
endif()
MESSAGE( STATUS "AFTR_NBITS is ${AFTR_NBITS}" )

IF( AFTR_NBITS EQUAL "64" )
   set_property( GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON )
ELSE()
   set_property( GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF )
ENDIF()

#Set common variables. Each variable is set relative to user land or the engine src based on if Cmake is run from a
#Module or an engine build directory, respectively.
IF( aftrFlagThatIndicatesCMakeListsIsBeingExecutingInsideTheEngineDirectorySoPathsShouldReflectEngineBuildAsRootOfCmake )
   SET( AFTR_USERLAND_ROOT_DIR "${CMAKE_SOURCE_DIR}/../../../usr" )
   SET( CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../../lib${AFTR_NBITS}" )
ELSE()
   SET( AFTR_USERLAND_ROOT_DIR "${CMAKE_SOURCE_DIR}/../../.." )
   SET( CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../../../lib${AFTR_NBITS}" )
ENDIF()
SET( AFTR_ENGINE_ROOT_DIR "${AFTR_USERLAND_ROOT_DIR}/../engine" )
SET( AFTR_ENGINE_SRC_DIR "${AFTR_ENGINE_ROOT_DIR}/src/aftr" )
SET( CMAKE_MODULE_PATH "${AFTR_ENGINE_ROOT_DIR}/src/cmake" )
SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${AFTR_USERLAND_ROOT_DIR}/include/cmake" )
SET( AFTR_USR_INCLUDE_DIR "${AFTR_USERLAND_ROOT_DIR}/include/aftr" )
if( aftrFlagThatIndicatesCMakeListsIsBeingExecutingInsideTheEngineDirectorySoPathsShouldReflectEngineBuildAsRootOfCmake )
   SET( AFTR_3RD_PARTY_INCLUDE_ROOT "${AFTR_ENGINE_ROOT_DIR}/src/" )
else()
   SET( AFTR_3RD_PARTY_INCLUDE_ROOT "${AFTR_USERLAND_ROOT_DIR}/include" )
endif()
SET( AFTR_BINARY_DIR ${CMAKE_BINARY_DIR} )
SET( AFTR_USERLAND_LIB_PATH "${AFTR_USERLAND_ROOT_DIR}/lib${AFTR_NBITS}" )
SET( CMAKE_INSTALL_PREFIX "${AFTR_USERLAND_ROOT_DIR}" CACHE PATH "Default Install Location is in User land so modules can automatically find, include, and link" FORCE )

#This will produce a compile_commands.json that tools such as VS Code can use to populate its intellisense.
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

MakeAbsolute( CMAKE_LIBRARY_PATH )
MakeAbsolute( AFTR_USERLAND_ROOT_DIR )
MakeAbsolute( AFTR_ENGINE_ROOT_DIR )
MakeAbsolute( AFTR_ENGINE_SRC_DIR )
MakeAbsolute( CMAKE_MODULE_PATH )
MakeAbsolute( AFTR_USR_INCLUDE_DIR )
MakeAbsolute( AFTR_3RD_PARTY_INCLUDE_ROOT )
MakeAbsolute( AFTR_BINARY_DIR )
MakeAbsolute( AFTR_USERLAND_LIB_PATH )
MakeAbsolute( CMAKE_INSTALL_PREFIX )

MESSAGE( STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}" )

MESSAGE( STATUS "Importing aftr engine now... Ensure it has already been built with the desired configuration..." )
# Perform initial search for dependencies to build
MESSAGE( STATUS " --- Boost Libraries --- " )
set( BOOST_ROOT $ENV{BOOST_ROOT} )
set( BOOST_INCLUDEDIR $ENV{BOOST_INCLUDEDIR} )
set( BOOST_LIBRARYDIR $ENV{BOOST_LIBRARYDIR} )
MESSAGE( STATUS " For Windows installs: Ensure you have created the following BOOST Specific" )
MESSAGE( STATUS " environmental variables configured on your machine. Boost uses these variables" )
MESSAGE( STATUS " as hints within its own FindBoost.cmake module. The 3 hints are:")
   MESSAGE( STATUS "   BOOST_ROOT - Preferred installation prefix (or BOOSTROOT)" )
   MESSAGE( STATUS "   BOOST_INCLUDEDIR       - Preferred include directory e.g. <prefix>/include" )
   MESSAGE( STATUS "   BOOST_LIBRARYDIR       - Preferred library directory e.g. <prefix>/lib" )
   MESSAGE( STATUS "   Currently CMAKE believes the 3 boost environment variables listed above are:" )
   MESSAGE( STATUS "ENV{BOOST_ROOT}           : $ENV{BOOST_ROOT}" )
   MESSAGE( STATUS "ENV{BOOST_INCLUDEDIR}     : $ENV{BOOST_INCLUDEDIR}" )
   MESSAGE( STATUS "ENV{BOOST_LIBRARYDIR}     : $ENV{BOOST_LIBRARYDIR}" )
set( Boost_DEBUG ON )
set( Boost_USE_STATIC_RUNTIME OFF )
set( Boost_USE_STATIC_LIBS   ON )
set( Boost_USE_MULTITHREADED ON )
FIND_PACKAGE( Boost 1.55.0 COMPONENTS regex thread filesystem timer date_time system chrono atomic iostreams log )
if( Boost_FOUND )
   MESSAGE( STATUS "Boost include        : ${Boost_INCLUDE_DIRS}" )   
   MESSAGE( STATUS "Boost_LIBRARY_DIRS   : ${Boost_LIBRARY_DIRS}" )
   MESSAGE( STATUS "Boost component libs : ${Boost_LIBRARIES}" )
else()
   MESSAGE( "Boost 1.55.0 or greater not found." )
   MESSAGE( "On *NIX, install 'apt-get install libboost1.55-all-dev' (if using APT via Debian. Otherwise use your distro's package manager to install Boost 1.55.0 or greater)." )
   MESSAGE( "For Windows: To Find Boost Libraries, create environment variable call BOOST_LIBRARYDIR and point to lib folder. Or set CMAKE Variables BOOST_LIBRARY_DIRS and BOOST_LIBRARYDIR as well as Boost_INCLUDE_DIRS (case sensitive) to point at your boost install." )
endif()
MESSAGE( STATUS " ----------------------- " )
MESSAGE( STATUS "" )
MESSAGE( STATUS " --- SDL2 Libraries ---- " )
FIND_PACKAGE( SDL2 2.0.1 REQUIRED )
if( SDL2_FOUND )
   MESSAGE( STATUS "***Found SDL2." )
   MESSAGE( STATUS "   SDL2 Include (SDL2_INCLUDE_DIR): ${SDL2_INCLUDE_DIR}")
   MESSAGE( STATUS "   SDL2 Libs (SDL2_LIBRARY): ${SDL2_LIBRARY}" )
   MESSAGE( STATUS "   SDL2_LIBRARIES: ${SDL2_LIBRARIES}" )
else()
   MESSAGE( "SDL2 2.0.1 or greater not found." )
   MESSAGE( "On *NIX, use your package manager to install libSDL2, or goto engine/src/SDL2, unzip archive file and configure, make, make install, yourself." )
endif()
MESSAGE( STATUS " ----------------------- " )
MESSAGE( STATUS "" )
MESSAGE( STATUS " ---SDL2 Image---------- " )
FIND_PACKAGE( SDL2Image 2.0.0 REQUIRED )
if( SDL2Image_FOUND )
   MESSAGE( STATUS "***Found SDL2." )
   MESSAGE( STATUS "   SDL2 Image Include (SDL2Image_INCLUDE_DIR): ${SDL2Image_INCLUDE_DIR}")
   MESSAGE( STATUS "   SDL2 Image Libs (SDL2Image_LIBRARY): ${SDL2Image_LIBRARY}" )
   MESSAGE( STATUS "   SDL2 Image Libs Debug (SDL2Image_LIBRARY_DEBUG): ${SDL2Image_LIBRARY_DEBUG}" )
else()
   MESSAGE( "SDL2Image 2.0.0 or greater not found." )
   MESSAGE( "On *NIX, use your package manager to install libsdl2-image-2.0-0, or goto engine/src/SDL2_image-2.0.2, unzip archive file and configure, make, make install, yourself." )
endif()
MESSAGE( STATUS " ----------------------- " )
MESSAGE( STATUS "" )
MESSAGE( STATUS " ---GDAL---------------- " )
FIND_PACKAGE( GDAL 1.11.0 )
if( GDAL_FOUND )
   MESSAGE( STATUS "***Found GDAL." )
   MESSAGE( STATUS "   GDAL Include (GDAL_INCLUDE_DIR): ${GDAL_INCLUDE_DIR}")
   MESSAGE( STATUS "   GDAL Libs (GDAL_LIBRARY): ${GDAL_LIBRARY}" )
else()
   MESSAGE( WARNING "GDAL 1.11.0 or greater not found." )
   MESSAGE( WARNING "On *NIX, use your package manager to install GDAL, or goto engine/src/gdal.1.11.0, unzip archive file and configure, make, make install, yourself (your distro packager may not have gdal-1.11.0 available)." )
   MESSAGE( WARNING "On windows this is usually not a problem since this library is embedded in this repo. This section may be ignored. " )
endif()
MESSAGE( STATUS " ----------------------- " )
MESSAGE( STATUS "" )
MESSAGE( STATUS " ---ASSIMP---------------- " )
FIND_PACKAGE( ASSIMP )
if( assimp_FOUND )
   MESSAGE( STATUS "***Found assimp." )
   MESSAGE( STATUS "   ASSIMP Include (ASSIMP_INCLUDE_DIR) : ${ASSIMP_INCLUDE_DIR}")
   MESSAGE( STATUS "   ASSIMP Libs (ASSIMP_LIBRARY)        : ${ASSIMP_LIBRARY}" )
   MESSAGE( STATUS "   Release Lib (ASSIMP_LIBRARY_RELEASE): ${ASSIMP_LIBRARY_RELEASE}")
   MESSAGE( STATUS "     Debug Lib (ASSIMP_LIBRARY_RELEASE): ${ASSIMP_LIBRARY_DEBUG}")
   MESSAGE( STATUS "   ASSIMP Libs dir (ASSIMP_LIBRARY_DIR): ${ASSIMP_LIBRARY_DIR}" )
else()
   MESSAGE( WARNING "ASSMIP 3.3.0 or greater not found." )
   MESSAGE( WARNING "On *NIX, use your package manager to install ASSMIP, or goto engine/src/assimp-3.3.1, unzip archive file and use cmake to configure then make and install, yourself (your distro packager may not have assimp-3.3.1 available)." )
   MESSAGE( WARNING "On windows this is usually not a problem since this library is embedded in this repo. This section may be ignored. " )
endif()
MESSAGE( STATUS " ----------------------- " )
MESSAGE( STATUS "" )
MESSAGE( STATUS " ---Freetype2----------- " )
FIND_PACKAGE( Freetype 2.5.3 )
if( FREETYPE_FOUND )
   MESSAGE( STATUS "***Found Freetype." )
   MESSAGE( STATUS "   Freetype Include (FREETYPE_INCLUDE_DIRS): ${FREETYPE_INCLUDE_DIRS}")
   MESSAGE( STATUS "   Freetype Libs (FREETYPE_LIBRARIES): ${FREETYPE_LIBRARIES}" )
else()
   if( WIN32 )
      MESSAGE( STATUS "On Windows, this build is using ../src/freetype-2.9" )
   else()
      MESSAGE( WARNING "FreeTye 2.5.3 or greater not found.\n"
                       "On *NIX, use your package manager to install freetype-2.5+ (sudo apt-get install libfreetyp6-dev), or goto engine/src/freetype-2.5.3, unzip archive file and finally configure, make, make install, yourself.\n" )
   endif()
endif()
MESSAGE( STATUS " ----------------------- " )

#If cmake doesn't find boost, let the user point to the directory
SET( Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} CACHE PATH "Path to BOOST 1.55.0 or greater header files." )
SET( BOOST_LIBRARYDIR ${BOOST_LIBRARYDIR} CACHE PATH "Path to BOOST 1.55.0 or greater libraries (.libs/.dlls)." FORCE )

#If cmake cannot find assimp, let the user point to the directory
SET( ASSIMP_INCLUDE_DIR ${ASSIMP_INCLUDE_DIRS} CACHE PATH "Path to Assimp 3.0.0 or greater header files.")
SET( ASSIMP_LIBRARY_DIR ${ASSIMP_LIBRARY_DIRS} CACHE PATH "Path to Assimp 3.0.0 or greater libraries (.libs/.dlls)." )

#Here we set some default paths for SDL. This will not work on all platforms. This is here to hopefully help
#windows set the correct include paths and lib paths. Linux and Apple should be able to successfully use 
#FIND_PACKAGE(...).
SET( SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR} CACHE PATH "Path to SDL2-2.0.7 include files" )


#Now we define some global compiler flags that we would like to have specified to BOTH the engine and all modules.
#This is nice in that adding a compiler flag here affects ALL modules that include this file as well as the engine
#making this a convenient place to manage repo-wide build settings
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
   SET( warnings "${warnings} -Wall -Wextra -Wno-overloaded-virtual -Wno-unused-parameter -Wno-unknown-pragmas -Wfatal-errors" ) #not using -Werror
   SET( cppFlags "${cppFlags} -fpermissive -std=c++17 -fdiagnostics-color=auto" ) #GNU/Clang specific CPP compiler flags    
   ADD_DEFINITIONS( -DAFTR_UNIX )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
   SET( CMAKE_CXX_FLAGS "" )
   SET( warnings "${warnings} /DWIN32 /D_WINDOWS" )
   SET( warnings "${warnings} /W3" )   
   SET( warnings "${warnings} /wd4100" ) #disable warning: 'identifier' : unreferenced formal parameter
   SET( warnings "${warnings} /D_SCL_SECURE_NO_WARNINGS" ) #disable warning:  warning C4996: 'std::_Copy_impl': Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct.
   SET( warnings "${warnings} /D_WIN32_WINNT=0x0501" ) #disable warning: Informs compiler that Windows XP is explicitly the minimum required
   SET( warnings "${warnings} /D_WINSOCK_DEPRECATED_NO_WARNINGS" ) #disable warning: Boost ASIO uses deprecated Windows API. This silences that warning
   SET( warnings "${warnings} /DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE" ) #Disable MSVC complaints about old boost
   SET( warnings "${warnings} /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING" ) #Disable MSVC complaints about C++17 allocator warnings. Added with Boost 1.69
   SET( warnings "${warnings} /D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS" ) #Disable MSVC complaints about C++17 allocator warnings. Added with Boost 1.69
   SET( warnings "${warnings} /we4703 /we4701" ) #treat potentially uninitialized local variable or pointer as an error
   SET( cppFlags "${cppFlags} /GR /EHsc" )
   SET( cppFlags "${cppFlags} /MP" ) #MSVC Specific CPP compiler flags, MP=Multi Processor compilations
   SET( cppFlags "${cppFlags} /std:c++17" ) #MSVC Specific CPP compiler flags, MP=Multi Processor compilations
   ADD_DEFINITIONS( -DAFTR_MSVC )
endif()

MESSAGE( STATUS "Using Compiler ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}.")

MESSAGE( STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ]\n"
                 "   set warnings to: ${warnings}\n"
                 "   set cppFlags to: ${cppFlags}\n" )

MESSAGE( STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
                 "LEAVING aftrModuleCMakeHelper.cmake..." )
