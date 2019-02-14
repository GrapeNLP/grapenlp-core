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

project(pygrapenlp VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -DSIMPLIFIED_OUTPUT -DSWIG_STD_MODERN_STL -DSWIG_EXPORT_ITERATOR_METHODS -DDISABLE_TEXT_DICO -DDISABLE_LUA_GRAMMAR -DDISABLE_LUAW_GRAMMAR -DDISABLE_LUT_GRAMMAR -DDISABLE_LUX_GRAMMAR -DDISABLE_DEPTH_FIRST_PARSER -DDISABLE_BREADTH_FIRST_PARSER -DDISABLE_EARLEY_PARSER -DDISABLE_TO_FPRTN_PARSER -DDISABLE_TO_FPRTN_TOP_PARSER -DDISABLE_TO_FPRTN_ZPPS_PARSER -DDISABLE_TO_FPRTN_PARSER_AND_BREADTH_FIRST_EXPANDER -DDISABLE_TO_FPRTN_PARSER_AND_BLACKBOARD_SET_EXPANDER -DDISABLE_STD_SES -DDISABLE_LRB_TREE_3W_SES -DDISABLE_LRB_TREE_BS -DDISABLE_LRB_TREE_3W_BS")
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/python/pygrapenlp")
set(SWIG_OUTFILE_DIR "${CMAKE_BINARY_DIR}/python/pygrapenlp")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set_property(SOURCE swig/grapenlp/pygrapenlp.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE swig/grapenlp/pygrapenlp.i PROPERTY SWIG_FLAGS "-includeall" "-py3" "-extranative")
if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    swig_add_module(pygrapenlp python swig/grapenlp/pygrapenlp.i)
else (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    swig_add_library(pygrapenlp TYPE SHARED LANGUAGE python SOURCES swig/grapenlp/pygrapenlp.i)
endif (${CMAKE_VERSION} VERSION_LESS "3.8.0")
swig_link_libraries(pygrapenlp
        manager
        ${PYTHON_LIBRARIES}
        )

install(DIRECTORY "${CMAKE_BINARY_DIR}/python"
        DESTINATION "src/grapenlp"
        COMPONENT libgrapenlpdev)
