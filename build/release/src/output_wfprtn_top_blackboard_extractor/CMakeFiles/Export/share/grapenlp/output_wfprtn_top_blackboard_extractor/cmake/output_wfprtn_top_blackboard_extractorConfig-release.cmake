#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "output_wfprtn_top_blackboard_extractor" for configuration "Release"
set_property(TARGET output_wfprtn_top_blackboard_extractor APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(output_wfprtn_top_blackboard_extractor PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liboutput_wfprtn_top_blackboard_extractor.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS output_wfprtn_top_blackboard_extractor )
list(APPEND _IMPORT_CHECK_FILES_FOR_output_wfprtn_top_blackboard_extractor "${_IMPORT_PREFIX}/lib/liboutput_wfprtn_top_blackboard_extractor.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
