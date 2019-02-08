#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "stats" for configuration "Release"
set_property(TARGET stats APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(stats PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libstats.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS stats )
list(APPEND _IMPORT_CHECK_FILES_FOR_stats "${_IMPORT_PREFIX}/lib/libstats.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
