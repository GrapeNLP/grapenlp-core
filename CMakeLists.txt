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

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
set(CMAKE_VERBOSE_MAKEFILE on)

include(VersionFromChangelog)

set(CPACK_PACKAGE_NAME "grapenlp")
set(CPACK_PACKAGE_VERSION "${CHANGELOG_VERSION}")
set(CPACK_PACKAGE_VENDOR "GrapeNLP")
set(CPACK_PACKAGE_CONTACT "Javier Sastre <javier.sastre@telefonica.net>")
set(CPACK_SOURCE_IGNORE_FILES
    ${CPACK_SOURCE_IGNORE_FILES}
    "/test\\\\.txt"
    "/trace\\\\.txt"
    "/result\\\\.txt"
    "/grammar\\\\.dot"
    "/grammar\\\\.svg"
    "/dirty_parses\\\\.dot"
    "/dirty_parses\\\\.svg"
    "/inv_parses\\\\.dot"
    "/inv_parses\\\\.svg"
    "/parses\\\\.dot"
    "/parses\\\\.svg"
    "/Data/"
    "/build/"
    "/scripts/"
    "/\\\\.git/"
    "/\\\\.gitignore"
    "/\\\\.idea/"
    "/.*\\\\.iml"
    "/cmake-build-.*/"
    "/\\\\.travis.yml"
)

MESSAGE(STATUS "BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "CHANGELOG_VERSION: ${CHANGELOG_VERSION}")

if (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
    # Enable testing for non-Android compilations
    # TODO: support running tests in Android continuous integration workflow by using some emulator (qemu?)
    include(CTest)
    MESSAGE(STATUS "BUILD_TESTING: ${BUILD_TESTING}")
endif (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)

add_subdirectory(src)
