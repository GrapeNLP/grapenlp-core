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

project(libjgrapenlp VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -DSIMPLIFIED_OUTPUT -DSWIG_STD_MODERN_STL -DSWIG_EXPORT_ITERATOR_METHODS -DDISABLE_TEXT_DICO -DDISABLE_LUA_GRAMMAR -DDISABLE_LUAW_GRAMMAR -DDISABLE_LUT_GRAMMAR -DDISABLE_LUX_GRAMMAR -DDISABLE_DEPTH_FIRST_PARSER -DDISABLE_BREADTH_FIRST_PARSER -DDISABLE_EARLEY_PARSER -DDISABLE_TO_FPRTN_PARSER -DDISABLE_TO_FPRTN_TOP_PARSER -DDISABLE_TO_FPRTN_ZPPS_PARSER -DDISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER -DDISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER -DDISABLE_STD_SES -DDISABLE_LRB_TREE_3W_SES -DDISABLE_LRB_TREE_BS -DDISABLE_LRB_TREE_3W_BS")
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-package" "com.grapenlp.core")
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/java/com/grapenlp/core")
set_property(SOURCE swig/grapenlp/jgrapenlp.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE swig/grapenlp/jgrapenlp.i PROPERTY SWIG_FLAGS "-includeall")
if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    swig_add_module(jgrapenlp java swig/grapenlp/jgrapenlp.i)
else (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    swig_add_library(jgrapenlp TYPE SHARED LANGUAGE java SOURCES swig/grapenlp/jgrapenlp.i)
endif (${CMAKE_VERSION} VERSION_LESS "3.8.0")
target_link_libraries(jgrapenlp
        manager
        ${JNI_LIBRARIES}
        )

install(TARGETS jgrapenlp EXPORT jgrapenlpConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libjgrapenlp)
install(EXPORT jgrapenlpConfig DESTINATION share/grapenlp/jgrapenlp/cmake COMPONENT libjgrapenlp)
install(FILES "${CMAKE_BINARY_DIR}/debian/copyright"
        "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/libjgrapenlp"
        COMPONENT libjgrapenlp)
install(DIRECTORY "${CMAKE_BINARY_DIR}/java"
        DESTINATION "src/grapenlp"
        COMPONENT libgrapenlpdev
        FILES_MATCHING PATTERN "*.java")
export(TARGETS jgrapenlp FILE jgrapenlpConfig.cmake)
