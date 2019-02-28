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

project(segment VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(segment STATIC
        src/out_bound.cpp
        src/u_out_bound.cpp
        src/out_bound_const_ref_x_weight.cpp
        src/u_out_bound_const_ref_x_weight.cpp
        src/segment.cpp
        src/segment_map_x_weight.cpp
        src/simple_segment.cpp
        src/simple_segment_array_x_weight.cpp
        )
target_include_directories(segment PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(segment
        assoc_container_impl_selector
        token
        )

install(TARGETS segment EXPORT segmentConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT segmentConfig DESTINATION share/grapenlp/segment/cmake COMPONENT libgrapenlpdev)
export(TARGETS segment FILE segmentConfig.cmake)
