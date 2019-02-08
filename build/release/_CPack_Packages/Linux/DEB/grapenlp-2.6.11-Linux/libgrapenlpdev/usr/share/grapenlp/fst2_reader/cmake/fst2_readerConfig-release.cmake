#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fst2_reader" for configuration "Release"
set_property(TARGET fst2_reader APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fst2_reader PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfst2_reader.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fst2_reader )
list(APPEND _IMPORT_CHECK_FILES_FOR_fst2_reader "${_IMPORT_PREFIX}/lib/libfst2_reader.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
