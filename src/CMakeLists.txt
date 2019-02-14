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

project(grapenlp-core VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)
configure_file (
        "${PROJECT_SOURCE_DIR}/config/include/grapenlp/config.h.in"
        "${PROJECT_BINARY_DIR}/config/include/grapenlp/config.h"
)
include_directories(${PROJECT_BINARY_DIR}/config/include)

include(MTraceBuildType)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -pedantic -ansi -fno-strict-aliasing -DSIMPLIFIED_OUTPUT")
if (ANDROID_NDK_TOOLCHAIN_INCLUDED)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DDISABLE_TEXT_DICO -DDISABLE_LUA_GRAMMAR -DDISABLE_LUAW_GRAMMAR -DDISABLE_LUT_GRAMMAR -DDISABLE_LUX_GRAMMAR -DDISABLE_DEPTH_FIRST_PARSER -DDISABLE_BREADTH_FIRST_PARSER -DDISABLE_EARLEY_PARSER -DDISABLE_TO_FPRTN_PARSER -DDISABLE_TO_FPRTN_TOP_PARSER -DDISABLE_TO_FPRTN_ZPPS_PARSER -DDISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER -DDISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER -DDISABLE_STD_SES -DDISABLE_LRB_TREE_3W_SES -DDISABLE_LRB_TREE_BS -DDISABLE_LRB_TREE_3W_BS")
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g0")
    endif (CMAKE_BUILD_TYPE STREQUAL "Release")
    MESSAGE(STATUS "Compiling Android version")
elseif (WIN32)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DWIN32")
    set(ADDITIONAL_SWIG_DEFINES ${ADDITIONAL_SWIG_DEFINES} -DWIN32)
elseif (UNIX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DUNIX")
    set(ADDITIONAL_SWIG_DEFINES ${ADDITIONAL_SWIG_DEFINES} -DUNIX)
endif (ANDROID_NDK_TOOLCHAIN_INCLUDED)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DTRACE")
MESSAGE(STATUS "CXX_FLAGS:" ${CMAKE_CXX_FLAGS})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_bin)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)
string(REPLACE "grapenlp-core" "grapenlp" CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_DOCDIR}")

if (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
    # Include system installed Boost as an imported target
    find_package(Boost QUIET REQUIRED COMPONENTS program_options)

    # Include Python
    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_PATH})

    # Include Java
    find_package(JNI REQUIRED)
    include_directories(${JAVA_INCLUDE_PATH})
    if (WIN32)
        include_directories(${JAVA_INCLUDE_PATH}/win32)
    elseif (UNIX)
        include_directories(${JAVA_INCLUDE_PATH}/linux)
    endif (WIN32)
endif (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
MESSAGE(STATUS "Boost_VERSION: ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
MESSAGE(STATUS "Boost_INCLUDE_DIR:" ${Boost_INCLUDE_DIR})
MESSAGE(STATUS "Boost_PROGRAM_OPTIONS_LIBRARY:" ${Boost_PROGRAM_OPTIONS_LIBRARY})

# Include Swig for building native library interfaces with Python and Java
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
if (WIN32)
    set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-DWIN32")
elseif (UNIX)
    set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-DUNIX" "-DSIMPLIFIED_OUTPUT")
endif (WIN32)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-DTRACE")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
MESSAGE(STATUS "CMAKE_SWIG_FLAGS: ${CMAKE_SWIG_FLAGS}")

include_directories(${Boost_INCLUDE_DIR})
#add_library(boost INTERFACE IMPORTED)
#set_property(TARGET boost PROPERTY

if (BUILD_TESTING)
include(GoogleTestDownload)
endif (BUILD_TESTING)

# Targets that we develop here
add_subdirectory(assoc_container_impl_selector)
add_subdirectory(breadth_first_parsing)
if (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
    add_subdirectory(cgrapenlp)
endif (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
add_subdirectory(compressed_delaf)
add_subdirectory(libgrapenlp)
add_subdirectory(delaf)
add_subdirectory(depth_first_parsing)
add_subdirectory(earley_parsing)
#add_subdirectory(fprtn)
#add_subdirectory(fprtn_to_dot_serializer)
#add_subdirectory(fst)
add_subdirectory(fst2_constants)
add_subdirectory(fst2_reader)
#if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_subdirectory(jgrapenlp)
#endif (CMAKE_BUILD_TYPE STREQUAL "Release")
add_subdirectory(lexmask)
add_subdirectory(lrb_tree)
add_subdirectory(lrb_tree_to_dot_serializer)
add_subdirectory(machine)
add_subdirectory(manager)
add_subdirectory(memory)
add_subdirectory(out_serializer)
add_subdirectory(output_fprtn)
add_subdirectory(output_fprtn_blackboard_set_expander)
add_subdirectory(output_fprtn_breadth_first_expander)
add_subdirectory(output_fprtn_prune)
add_subdirectory(output_fprtn_to_dot_serializer)
add_subdirectory(output_fprtn_top)
add_subdirectory(output_fprtn_top_prune)
add_subdirectory(output_fprtn_zpps)
add_subdirectory(output_fprtn_zpps_prune)
add_subdirectory(output_wfprtn_top_blackboard_extractor)
add_subdirectory(parsing)
#add_subdirectory(pcfgla)
#add_subdirectory(pcfgla_to_rtno)
if (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_subdirectory(pygrapenlp)
endif (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
add_subdirectory(rb_tree)
add_subdirectory(rb_tree_to_dot_serializer)
add_subdirectory(rtno)
add_subdirectory(rtno_to_dot_serializer)
add_subdirectory(segment)
#add_subdirectory(simplify_templates)
add_subdirectory(stats)
add_subdirectory(text_delaf)
add_subdirectory(to_canonical_form)
add_subdirectory(to_decompressed_canonical_form)
add_subdirectory(to_fprtn_parsing)
add_subdirectory(to_fprtn_top_parsing)
add_subdirectory(to_fprtn_zpps_parsing)
#add_subdirectory(to_gnuplot)
add_subdirectory(tokenization)
add_subdirectory(util)
add_subdirectory(unicode)

# Packaging stuff
if (UNIX AND NOT APPLE AND NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
    get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
    # Remove the "trash" component from the list of components to install; this avoids 3rd party components (e.g.
    # GoogleTest) to be packaged along with the files of this project
    list(REMOVE_ITEM CPACK_COMPONENTS_ALL "trash")
    MESSAGE(STATUS "CPACK_COMPONENTS_ALL: ${CPACK_COMPONENTS_ALL}")
    set(CPACK_OUTPUT_FILE_PREFIX package)
    include(DebianPackaging)
    include(CPack)
    include(UploadPPA)
endif (UNIX AND NOT APPLE AND NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
