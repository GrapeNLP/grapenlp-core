#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "output_fprtn_to_dot_serializer" for configuration "Release"
set_property(TARGET output_fprtn_to_dot_serializer APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(output_fprtn_to_dot_serializer PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liboutput_fprtn_to_dot_serializer.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS output_fprtn_to_dot_serializer )
list(APPEND _IMPORT_CHECK_FILES_FOR_output_fprtn_to_dot_serializer "${_IMPORT_PREFIX}/lib/liboutput_fprtn_to_dot_serializer.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
