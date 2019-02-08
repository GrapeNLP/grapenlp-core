#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "grapenlp" for configuration "Release"
set_property(TARGET grapenlp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(grapenlp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libgrapenlp.so"
  IMPORTED_SONAME_RELEASE "libgrapenlp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS grapenlp )
list(APPEND _IMPORT_CHECK_FILES_FOR_grapenlp "${_IMPORT_PREFIX}/lib/libgrapenlp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
