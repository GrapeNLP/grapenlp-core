#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "jgrapenlp" for configuration "Release"
set_property(TARGET jgrapenlp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(jgrapenlp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libjgrapenlp.so"
  IMPORTED_SONAME_RELEASE "libjgrapenlp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS jgrapenlp )
list(APPEND _IMPORT_CHECK_FILES_FOR_jgrapenlp "${_IMPORT_PREFIX}/lib/libjgrapenlp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
