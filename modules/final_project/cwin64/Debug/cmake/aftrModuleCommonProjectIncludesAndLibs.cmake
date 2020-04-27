#####This section adds in other libraries, including AftrBurner, as well as other include paths
#####that were not added as part of the FIND_PACKAGE calls above.
include(CheckSymbolExists)
include ( "${AFTR_3RD_PARTY_INCLUDE_ROOT}/cmake/aftr-targets.cmake" )  #We are using the CMake install target files generated by the engine.
# This is the path to the aftr libs as specified within the engine build "install" and exported into the aftr-targets.cmake above.
GET_PROPERTY( aftrLibPathMinSizeRel TARGET AftrBurnerEngine PROPERTY IMPORTED_LOCATION_MINSIZEREL )
#GET_PROPERTY( aftrLibPathRelease TARGET AftrBurnerEngine PROPERTY IMPORTED_LOCATION_RELEASE )
GET_PROPERTY( aftrLibPathDebug TARGET AftrBurnerEngine PROPERTY IMPORTED_LOCATION_DEBUG )
#GET_PROPERTY( aftrLibPathRelWithDebInfo TARGET AftrBurnerEngine PROPERTY IMPORTED_LOCATION_RELWITHDEBINFO )

MESSAGE( STATUS "aftrLibPathMinSizeRel     is: ${aftrLibPathMinSizeRel}" )
MESSAGE( STATUS "aftrLibPathRelease        is: ${aftrLibPathRelease}" )
MESSAGE( STATUS "aftrLibPathDebug          is: ${aftrLibPathDebug}" )
MESSAGE( STATUS "aftrLibPathRelWithDebInfo is: ${aftrLibPathRelWithDebInfo}" )

MESSAGE( STATUS "Build path is ${CMAKE_CURRENT_BINARY_DIR}" )
MESSAGE( "" )
ADD_EXECUTABLE( ${PROJECT_NAME} ${sources} ${headers} )


TARGET_LINK_LIBRARIES( ${PROJECT_NAME} AftrBurnerEngine ) #Can specify release, debug, relminsize, relwithdebinfo here as last param

#Let's check the userland's AftrConfig.h for certain #defines, like AFTR_CONFIG_USE_OCULUS_RIFT_OVR
#if that is used, then include the corresponding header files and library linker information
CHECK_SYMBOL_EXISTS( "AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS" "${AFTR_USR_INCLUDE_DIR}/AftrConfig.h" AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS )
IF( NOT AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS )
   SET( AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS "0" )
ENDIF()
MESSAGE( STATUS "AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS is: ${AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS}" )

CHECK_SYMBOL_EXISTS( "AFTR_CONFIG_USE_FONTS" "${AFTR_USR_INCLUDE_DIR}/AftrConfig.h" AFTR_CONFIG_USE_FONTS )
IF( NOT AFTR_CONFIG_USE_FONTS )
   SET( AFTR_CONFIG_USE_FONTS "0" )
ENDIF()
MESSAGE( STATUS "AFTR_CONFIG_USE_FONTS is: ${AFTR_CONFIG_USE_FONTS}" )

CHECK_SYMBOL_EXISTS( "AFTR_CONFIG_USE_OCULUS_RIFT_OVR" "${AFTR_USR_INCLUDE_DIR}/AftrConfig.h" AFTR_CONFIG_USE_OCULUS_RIFT_OVR )
IF( NOT AFTR_CONFIG_USE_OCULUS_RIFT_OVR )
   SET( AFTR_CONFIG_USE_OCULUS_RIFT_OVR "0" )
ENDIF()
MESSAGE( STATUS "AFTR_CONFIG_USE_OCULUS_RIFT_OVR is: ${AFTR_CONFIG_USE_OCULUS_RIFT_OVR}" )

CHECK_SYMBOL_EXISTS( "AFTR_CONFIG_USE_OCULUS_RIFT_DK2" "${AFTR_USR_INCLUDE_DIR}/AftrConfig.h" AFTR_CONFIG_USE_OCULUS_RIFT_DK2 )
IF( NOT AFTR_CONFIG_USE_OCULUS_RIFT_DK2 )
   SET( AFTR_CONFIG_USE_OCULUS_RIFT_DK2 "0" )
ENDIF()
MESSAGE( STATUS "AFTR_CONFIG_USE_OCULUS_RIFT_DK2 is: ${AFTR_CONFIG_USE_OCULUS_RIFT_DK2}" )

CHECK_SYMBOL_EXISTS( "AFTR_CONFIG_USE_KEYLOK_DONGLE" "${AFTR_USR_INCLUDE_DIR}/AftrConfig.h" AFTR_CONFIG_USE_KEYLOK_DONGLE )
IF( NOT AFTR_CONFIG_USE_KEYLOK_DONGLE )
   SET( AFTR_CONFIG_USE_KEYLOK_DONGLE "0" )
ENDIF()
MESSAGE( STATUS "AFTR_CONFIG_USE_KEYLOK_DONGLE is: ${AFTR_CONFIG_USE_KEYLOK_DONGLE}" )

CHECK_SYMBOL_EXISTS( "AFTR_CONFIG_USE_ASSIMP" "${AFTR_USR_INCLUDE_DIR}/AftrConfig.h" AFTR_CONFIG_USE_ASSIMP )
IF( NOT AFTR_CONFIG_USE_ASSIMP )
   SET( AFTR_CONFIG_USE_ASSIMP "0" )
ENDIF()
MESSAGE( STATUS "AFTR_CONFIG_USE_ASSIMP is: ${AFTR_CONFIG_USE_ASSIMP}" )

#using find_package for SDL and boost, every platform includes the headers and libraries the same way,
#but for packages that don't have the Find<MyLib>.cmake in the /engine/src/cmake folder, we have to manually add them per platform
IF( WIN32 )

   #Specific libraries need a msvc14 specific version.
   #MSVC 14 cannot link against some libs built by a version earlier than msvc 14.
#    IF( CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0.23026.0 ) #first offical release of MSVC14
#       SET( localSDLLibOptimized ${SDL2_LIBRARY} )
#       SET( localSDLLibDebug ${SDL2_LIBRARY_DEBUG} )
#       MESSAGE( STATUS "Using less than MSVC 14 for SDLmain: localSDLLibOptimized is ${localSDLLibOptimized}" )
#       MESSAGE( STATUS "Using less than MSVC 14 for SDLmain: localSDLLibDebug     is ${localSDLLibDebug}" )
#       SET( localFreeType253Optimized "${AFTR_USERLAND_LIB_PATH}/freetype253MT.lib" )
#       SET( localFreeType253Debug     "${AFTR_USERLAND_LIB_PATH}/freetype253MT_debug.lib" )
#       MESSAGE( STATUS "Using less than MSVC 14 for freetype253: localFreeType253Optimized is ${localFreeType253Optimized}" )
#       MESSAGE( STATUS "Using less than MSVC 14 for freetype253: localFreeType253Debug     is ${localFreeType253Debug}" )
#    ELSE()
       #SET( localSDLLibOptimized "${AFTR_USERLAND_LIB_PATH}/SDL2main.lib;${AFTR_USERLAND_LIB_PATH}/SDL2.lib" )
       #SET( localSDLLibDebug     "${AFTR_USERLAND_LIB_PATH}/SDL2main_debug.lib;${AFTR_USERLAND_LIB_PATH}/SDL2_debug.lib" )
       MESSAGE( STATUS "SDL2: {SDL2_LIBRARY}      : ${SDL2_LIBRARY}" )
       MESSAGE( STATUS "SDL2: {SDL2_LIBRARY_DEBUG}: ${SDL2_LIBRARY_DEBUG}" )
       SET( localFreeType29Optimized "${AFTR_USERLAND_LIB_PATH}/freetype.lib" )
       SET( localFreeType29Debug     "${AFTR_USERLAND_LIB_PATH}/freetype_debug.lib" )
       MESSAGE( STATUS "Font freetype2.9: {localFreeType29Optimized} is ${localFreeType29Optimized}" )
       MESSAGE( STATUS "Font freetype2.9: {localFreeType29Debug}     is ${localFreeType29Debug}" )
#    ENDIF()

   TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                          "opengl32.lib" #Required for Windows
                          "glu32.lib"
                optimized "${AFTR_USERLAND_LIB_PATH}/glew32s.lib"
                    debug "${AFTR_USERLAND_LIB_PATH}/glew32s_debug.lib"
                optimized "${SDL2_LIBRARY}"
                    debug "${SDL2_LIBRARY_DEBUG}"
               #optimized "${SDL2Image_LIBRARY}"
               #    debug "${SDL2Image_LIBRARY_DEBUG}"
                           ${SDL2Image_LIBRARIES} #This embeds optimized/debug versions
                optimized "${AFTR_USERLAND_LIB_PATH}/ode_single.lib"
                    debug "${AFTR_USERLAND_LIB_PATH}/ode_singled.lib"
                          "${AFTR_USERLAND_LIB_PATH}/gdal_i.lib"
                          "${AFTR_USERLAND_LIB_PATH}/lib3ds.lib"
                          ${Boost_LIBRARIES}
                        )

#    IF( "${AFTR_CONFIG_USE_FONTS}" STREQUAL "1" )
#       TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
#                 optimized "${localFreeType253Optimized}"
#                     debug "${localFreeType253Debug}"
#                            )
#    ENDIF()

   IF( "${AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS}" STREQUAL "1" )
      TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                optimized "${AFTR_USERLAND_LIB_PATH}/freetype.lib"
                    debug "${AFTR_USERLAND_LIB_PATH}/freetype_debug.lib"
                           )
   ENDIF()

   IF( "${AFTR_CONFIG_USE_OCULUS_RIFT_OVR}" STREQUAL "1" )
      TARGET_LINK_LIBRARIES( ${PROJECT_NAME}                          
                optimized "${AFTR_USERLAND_LIB_PATH}/libOVR.lib"
                    debug "${AFTR_USERLAND_LIB_PATH}/libOVRd.lib"
                           )
                           
      TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PRIVATE 
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/OculusSDK/ovr_sdk_win_1.26.0_public/OculusSDK/LibOVR/Include"
                                )                           
   ENDIF()

   IF( "${AFTR_CONFIG_USE_ASSIMP}" STREQUAL "1" )
      TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                optimized "${AFTR_USERLAND_LIB_PATH}/assimp-vc140-mt.lib"
                    debug "${AFTR_USERLAND_LIB_PATH}/assimp-vc140-mt_d.lib"
                           )
   ENDIF()

   IF( "${AFTR_CONFIG_USE_KEYLOK_DONGLE}" STREQUAL "1" )
      TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                optimized "${AFTR_USERLAND_LIB_PATH}/kfunc${AFTR_NBITS}MD.lib"
                    debug "${AFTR_USERLAND_LIB_PATH}/kfunc${AFTR_NBITS}MD.lib"
                           )
   ENDIF()
ENDIF()

IF( UNIX )
   TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                          "GLEW"
                          "GL"
                          "${SDL2_LIBRARY}"
                          "${SDL2_LIBRARY_DEBUG}"
                optimized "${SDL2Image_LIBRARY}"
                    debug "${SDL2Image_LIBRARY_DEBUG}"
                          "${GDAL_LIBRARY}"
                          "${Boost_LIBRARIES}"
                          "${FREETYPE_LIBRARIES}"
                          "3ds"
                          "ode"
                        )

   IF( "${AFTR_CONFIG_USE_ASSIMP}" STREQUAL "1" )
      TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                optimized "assimp"
                    debug "assimp"
                           )
   ENDIF()

ENDIF()

TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PRIVATE
                           "${AFTR_USR_INCLUDE_DIR}"
                           "${SDL2_INCLUDE_DIR}"
                           "${SDL2Image_INCLUDE_DIR}"
                           "${FREETYPE_INCLUDE_DIRS}"
                           "${GDAL_INCLUDE_DIR}"
                          )

TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PRIVATE
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/glew-2.1.0/include" #Used on Windows (linux should include from above)
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/glm-0.9.8.5/glm"
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/lib3ds-20080909/src"
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/gdal-1.11.0/include" #Used on Windows (linux should include from above)
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/freetype-2.5.5/include" #Used on Windows (linux should include from above)
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/ode-0.13/include" #Used on Windows (linux should include from above)
                           "${Boost_INCLUDE_DIRS}" #Include Boost headers
                          )

IF( "${AFTR_CONFIG_USE_OCULUS_RIFT_OVR}" STREQUAL "1" )
   TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PRIVATE
                           "${AFTR_3RD_PARTY_INCLUDE_ROOT}/OculusSDK" #Used on Windows (linux should include from above)
                          )
ENDIF()

