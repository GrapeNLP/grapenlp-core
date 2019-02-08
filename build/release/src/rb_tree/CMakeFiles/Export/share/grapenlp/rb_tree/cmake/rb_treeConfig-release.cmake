#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "rb_tree" for configuration "Release"
set_property(TARGET rb_tree APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(rb_tree PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/librb_tree.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS rb_tree )
list(APPEND _IMPORT_CHECK_FILES_FOR_rb_tree "${_IMPORT_PREFIX}/lib/librb_tree.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
