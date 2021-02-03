#
# GRAPENLP
#
# Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

project(libjgrapenlp VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -DSIMPLIFIED_OUTPUT -DSWIG_STD_MODERN_STL -DSWIG_EXPORT_ITERATOR_METHODS -DDISABLE_TEXT_DICO -DDISABLE_LUA_GRAMMAR -DDISABLE_LUAW_GRAMMAR -DDISABLE_LUT_GRAMMAR -DDISABLE_LUX_GRAMMAR -DDISABLE_DEPTH_FIRST_PARSER -DDISABLE_BREADTH_FIRST_PARSER -DDISABLE_EARLEY_PARSER -DDISABLE_TO_FPRTN_PARSER -DDISABLE_TO_FPRTN_TOP_PARSER -DDISABLE_TO_FPRTN_ZPPS_PARSER -DDISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER -DDISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER -DDISABLE_STD_SES -DDISABLE_LRB_TREE_3W_SES -DDISABLE_LRB_TREE_BS -DDISABLE_LRB_TREE_3W_BS")
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-package" "com.grapenlp.core")
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/java/com/grapenlp/core")
set_property(SOURCE swig/grapenlp/jgrapenlp.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE swig/grapenlp/jgrapenlp.i PROPERTY SWIG_FLAGS "-includeall")
# Old swig_add_module command does not honor library VERSION property, so a workaround is needed to generate the
# library with a version suffix and a symlink without the version suffix
if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    swig_add_module(jgrapenlp java swig/grapenlp/jgrapenlp.i)
    swig_link_libraries(jgrapenlp
            manager
            ${JNI_LIBRARIES}
            )
    # Make generated library to include version number after .so
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-soname,libjgrapenlp.so.${CHANGELOG_VERSION}")
    set_target_properties(jgrapenlp PROPERTIES SUFFIX ".so.${CHANGELOG_VERSION}")
    # Create symlink libjgrapenlp.so to libjgrapenlp.so.VERSION
    add_custom_command(OUTPUT "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libjgrapenlp.so"
            COMMAND ${CMAKE_COMMAND} -E create_symlink "libjgrapenlp.so.${CHANGELOG_VERSION}" "libjgrapenlp.so"
            DEPENDS jgrapenlp
            WORKING_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
            )
    add_custom_target(jgrapenlp_link ALL DEPENDS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libjgrapenlp.so")
else (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    swig_add_library(jgrapenlp TYPE SHARED LANGUAGE java SOURCES swig/grapenlp/jgrapenlp.i)
    target_link_libraries(jgrapenlp
            manager
            ${JNI_LIBRARIES}
            )
endif (${CMAKE_VERSION} VERSION_LESS "3.8.0")
set_target_properties (jgrapenlp PROPERTIES
        VERSION "${CHANGELOG_VERSION}"
        )

install(TARGETS jgrapenlp EXPORT jgrapenlpConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libjgrapenlp)
# Workaround to install the libjgrapenlp.so symlink
if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    install(FILES "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libjgrapenlp.so"
            DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libjgrapenlp)
endif (${CMAKE_VERSION} VERSION_LESS "3.8.0")
install(EXPORT jgrapenlpConfig DESTINATION share/grapenlp/jgrapenlp/cmake COMPONENT libjgrapenlp)
if (UNIX AND NOT APPLE AND NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
install(FILES "${CMAKE_BINARY_DIR}/debian/copyright"
        "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/libjgrapenlp"
        COMPONENT libjgrapenlp)
endif (UNIX AND NOT APPLE AND NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
install(DIRECTORY "${CMAKE_BINARY_DIR}/java"
        DESTINATION "src/grapenlp"
        COMPONENT libgrapenlpdev
        FILES_MATCHING PATTERN "*.java")
export(TARGETS jgrapenlp FILE jgrapenlpConfig.cmake)
