#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "to_fprtn_parsing" for configuration "Release"
set_property(TARGET to_fprtn_parsing APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(to_fprtn_parsing PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libto_fprtn_parsing.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS to_fprtn_parsing )
list(APPEND _IMPORT_CHECK_FILES_FOR_to_fprtn_parsing "${_IMPORT_PREFIX}/lib/libto_fprtn_parsing.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
