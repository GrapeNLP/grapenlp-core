#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "assoc_container_impl_selector" for configuration "Release"
set_property(TARGET assoc_container_impl_selector APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(assoc_container_impl_selector PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libassoc_container_impl_selector.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS assoc_container_impl_selector )
list(APPEND _IMPORT_CHECK_FILES_FOR_assoc_container_impl_selector "${_IMPORT_PREFIX}/lib/libassoc_container_impl_selector.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
