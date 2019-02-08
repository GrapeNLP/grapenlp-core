#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cgrapenlp" for configuration "Release"
set_property(TARGET cgrapenlp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cgrapenlp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/grapenlp"
  )

list(APPEND _IMPORT_CHECK_TARGETS cgrapenlp )
list(APPEND _IMPORT_CHECK_FILES_FOR_cgrapenlp "${_IMPORT_PREFIX}/bin/grapenlp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
