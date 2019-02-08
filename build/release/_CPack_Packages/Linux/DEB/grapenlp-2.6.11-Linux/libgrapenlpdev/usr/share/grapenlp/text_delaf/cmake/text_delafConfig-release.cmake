#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "text_delaf" for configuration "Release"
set_property(TARGET text_delaf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(text_delaf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libtext_delaf.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS text_delaf )
list(APPEND _IMPORT_CHECK_FILES_FOR_text_delaf "${_IMPORT_PREFIX}/lib/libtext_delaf.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
