# Install script for directory: /home/jmsma/src/GrapeNLP/grapenlp-core/src/jgrapenlp

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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libjgrapenlp" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/lib/libjgrapenlp.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so"
         OLD_RPATH "/usr/lib/jvm/jdk1.8.0/jre/lib/amd64:/usr/lib/jvm/jdk1.8.0/jre/lib/amd64/server:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjgrapenlp.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libjgrapenlp" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig.cmake"
         "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/src/jgrapenlp/CMakeFiles/Export/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grapenlp/jgrapenlp/cmake" TYPE FILE FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/src/jgrapenlp/CMakeFiles/Export/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/grapenlp/jgrapenlp/cmake" TYPE FILE FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/src/jgrapenlp/CMakeFiles/Export/share/grapenlp/jgrapenlp/cmake/jgrapenlpConfig-release.cmake")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libjgrapenlp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/grapenlp/libjgrapenlp" TYPE FILE FILES
    "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/debian/copyright"
    "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/debian/changelog.Debian.gz"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libgrapenlpdev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/src/grapenlp" TYPE DIRECTORY FILES "/home/jmsma/src/GrapeNLP/grapenlp-core/build/release/java" FILES_MATCHING REGEX "/[^/]*\\.java$")
endif()

