#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "compressed_delaf" for configuration "Release"
set_property(TARGET compressed_delaf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(compressed_delaf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcompressed_delaf.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS compressed_delaf )
list(APPEND _IMPORT_CHECK_FILES_FOR_compressed_delaf "${_IMPORT_PREFIX}/lib/libcompressed_delaf.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
