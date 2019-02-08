#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "output_fprtn_top_prune" for configuration "Release"
set_property(TARGET output_fprtn_top_prune APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(output_fprtn_top_prune PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liboutput_fprtn_top_prune.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS output_fprtn_top_prune )
list(APPEND _IMPORT_CHECK_FILES_FOR_output_fprtn_top_prune "${_IMPORT_PREFIX}/lib/liboutput_fprtn_top_prune.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
