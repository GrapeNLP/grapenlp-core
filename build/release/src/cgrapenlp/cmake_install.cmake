# Install script for directory: /home/jmsma/src/GrapeNLP/grapenlp-core/src/cgrapenlp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "cgrapenlp" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/bin/grapenlp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp"
         OLD_RPATH "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/grapenlp")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "cgrapenlp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/grapenlp/grapenlp" TYPE FILE FILES
    "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/debian/copyright"
    "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/debian/changelog.Debian.gz"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libgrapenlpdev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/grapenlp/cmake/cgrapenlpConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/grapenlp/cmake/cgrapenlpConfig.cmake"
         "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/src/cgrapenlp/CMakeFiles/Export/share/grapenlp/grapenlp/cmake/cgrapenlpConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/grapenlp/cmake/cgrapenlpConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/grapenlp/cmake/cgrapenlpConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grapenlp/grapenlp/cmake" TYPE FILE FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/src/cgrapenlp/CMakeFiles/Export/share/grapenlp/grapenlp/cmake/cgrapenlpConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grapenlp/grapenlp/cmake" TYPE FILE FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/src/cgrapenlp/CMakeFiles/Export/share/grapenlp/grapenlp/cmake/cgrapenlpConfig-release.cmake")
  endif()
endif()

