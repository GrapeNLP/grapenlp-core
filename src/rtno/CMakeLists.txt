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

project(rtno VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(rtno STATIC
        src/l_rtno.cpp
        src/lua_rtno.cpp
        src/luaw_rtno.cpp
        src/lux_rtno.cpp
        src/luxw_rtno.cpp
        src/lw_rtno_weight_tagger.cpp
        src/lw_rtno.cpp
        src/lt_rtno.cpp
        src/ltw_rtno.cpp
        src/lx_rtno.cpp
        src/lxw_rtno.cpp
        src/rtno_type.cpp
        src/rtno.cpp
        )
target_include_directories(rtno PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(rtno
        lrb_tree
        lexmask
        segment
        )

install(TARGETS rtno EXPORT rtnoConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT rtnoConfig DESTINATION share/grapenlp/rtno/cmake COMPONENT libgrapenlpdev)
export(TARGETS rtno FILE rtnoConfig.cmake)

add_executable(set_default_weights src/set_default_weights.cpp)
target_link_libraries(set_default_weights
        rtno
        fst2_reader
        rtno_to_dot_serializer
        )

#add_executable(c_set_default_weights src/c_set_default_weights.cpp)
#target_link_libraries(c_set_default_weights
#        rtno
#        fst2_reader
#        rtno_to_dot_serializer
#        )
