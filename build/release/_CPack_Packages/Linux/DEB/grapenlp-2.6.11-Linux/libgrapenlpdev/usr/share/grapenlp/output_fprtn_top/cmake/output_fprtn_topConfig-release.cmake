#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "output_fprtn_top" for configuration "Release"
set_property(TARGET output_fprtn_top APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(output_fprtn_top PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liboutput_fprtn_top.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS output_fprtn_top )
list(APPEND _IMPORT_CHECK_FILES_FOR_output_fprtn_top "${_IMPORT_PREFIX}/lib/liboutput_fprtn_top.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
