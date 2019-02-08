#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "to_decompressed_canonical_form" for configuration "Release"
set_property(TARGET to_decompressed_canonical_form APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(to_decompressed_canonical_form PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libto_decompressed_canonical_form.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS to_decompressed_canonical_form )
list(APPEND _IMPORT_CHECK_FILES_FOR_to_decompressed_canonical_form "${_IMPORT_PREFIX}/lib/libto_decompressed_canonical_form.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
