#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unicode" for configuration "Release"
set_property(TARGET unicode APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(unicode PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libunicode.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS unicode )
list(APPEND _IMPORT_CHECK_FILES_FOR_unicode "${_IMPORT_PREFIX}/lib/libunicode.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
