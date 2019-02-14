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

project(rb_tree_to_dot_serializer VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(rb_tree_to_dot_serializer STATIC src/rb_tree_to_dot_serializer.cpp)
target_include_directories(rb_tree_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(rb_tree_to_dot_serializer
        rb_tree
        machine
        )

install(TARGETS rb_tree_to_dot_serializer EXPORT rb_tree_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT rb_tree_to_dot_serializerConfig DESTINATION share/grapenlp/rb_tree_to_dot_serializer/cmake COMPONENT libgrapenlpdev)
export(TARGETS rb_tree_to_dot_serializer FILE rb_tree_to_dot_serializerConfig.cmake)
