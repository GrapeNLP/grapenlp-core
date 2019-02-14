#
# GRAPENLP
#
# Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
#
#
#
#
# @author Javier Sastre
#

# Check whether GoogleTest source is present in the file system or must be downloaded from GitHub
set(GOOGLETEST_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest_build")
if (EXISTS "/usr/src/googletest")
    set(GOOGLETEST_SOURCE_DIR "/usr/src/googletest")
    set(GOOGLETEST_CMAKE_IN "CMakeLists.txt.filesystem.in")
elseif (EXISTS "/usr/src/gtest")
    set(GOOGLETEST_SOURCE_DIR "/usr/src/gtest")
    set(GOOGLETEST_CMAKE_IN "CMakeLists.txt.filesystem.in")
else (EXISTS "/usr/src/googletest")
    set(GOOGLETEST_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest_src")
    set(GOOGLETEST_CMAKE_IN "CMakeLists.txt.github.in")
endif (EXISTS "/usr/src/googletest")

# Configure GoogleTest external project for the detected code source (filesystem or github) and download it if needed
configure_file(${PROJECT_SOURCE_DIR}/googletest_download/${GOOGLETEST_CMAKE_IN} ${CMAKE_CURRENT_BINARY_DIR}/googletest_download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest_download)
if(result)
    message(FATAL_ERROR "CMake step for GoogleTest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest_download )
if(result)
    message(FATAL_ERROR "Build step for GoogleTest failed: ${result}")
endif()

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Prevent GoogleTest from adding its files to the main project installation set
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${GOOGLETEST_SOURCE_DIR}
        ${GOOGLETEST_BINARY_DIR}
        EXCLUDE_FROM_ALL)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()
