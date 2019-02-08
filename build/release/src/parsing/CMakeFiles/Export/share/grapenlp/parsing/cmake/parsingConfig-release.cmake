#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "parsing" for configuration "Release"
set_property(TARGET parsing APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(parsing PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libparsing.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS parsing )
list(APPEND _IMPORT_CHECK_FILES_FOR_parsing "${_IMPORT_PREFIX}/lib/libparsing.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
