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

project(to_fprtn_top_parsing VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(to_fprtn_top_parsing STATIC
        src/to_fprtn_top_parser.cpp
        src/lua_to_fprtn_top_parser.cpp
        src/luaw_to_fprtn_top_parser.cpp
        src/lx_to_fprtn_top_parser.cpp
        src/lxw_to_fprtn_top_parser.cpp
        )
target_include_directories(to_fprtn_top_parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(to_fprtn_top_parsing
        rtno
        output_fprtn_top_prune
        )

install(TARGETS to_fprtn_top_parsing EXPORT to_fprtn_top_parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT to_fprtn_top_parsingConfig DESTINATION share/grapenlp/to_fprtn_top_parsing/cmake COMPONENT libgrapenlpdev)
export(TARGETS to_fprtn_top_parsing FILE to_fprtn_top_parsingConfig.cmake)
