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

project(earley_parsing VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(earley_parsing STATIC
        src/earley_parser.cpp
        src/earley_parser_no_output.cpp
        src/lua_earley_parser.cpp
        src/lua_earley_parser_no_output.cpp
        src/luaw_earley_parser.cpp
        src/luaw_earley_parser_no_output.cpp
        src/lx_earley_parser.cpp
        src/lx_earley_parser_no_output.cpp
        src/lxw_earley_parser.cpp
        src/lx_earley_parser_no_output.cpp
        )
target_include_directories(earley_parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(earley_parsing
        assoc_container_impl_selector
        context_mask
        rtno
        )

install(TARGETS earley_parsing EXPORT earley_parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT earley_parsingConfig DESTINATION share/grapenlp/earley_parsing/cmake COMPONENT libgrapenlpdev)
export(TARGETS earley_parsing FILE earley_parsingConfig.cmake)
