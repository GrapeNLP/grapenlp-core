#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "token" for configuration "Release"
set_property(TARGET token APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(token PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libtoken.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS token )
list(APPEND _IMPORT_CHECK_FILES_FOR_token "${_IMPORT_PREFIX}/lib/libtoken.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
