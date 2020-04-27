#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AftrBurnerEngine" for configuration "Debug"
set_property(TARGET AftrBurnerEngine APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(AftrBurnerEngine PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/AftrBurnerEngine_debug.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS AftrBurnerEngine )
list(APPEND _IMPORT_CHECK_FILES_FOR_AftrBurnerEngine "${_IMPORT_PREFIX}/lib64/AftrBurnerEngine_debug.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
