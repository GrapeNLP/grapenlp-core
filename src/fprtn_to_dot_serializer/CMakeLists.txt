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

project(fprtn_to_dot_serializer VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(fprtn_to_dot_serializer STATIC
        src/fprtn_to_dot_serializer.cpp
        src/inv_fprtn_to_dot_serializer.cpp
        )
target_include_directories(fprtn_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(fprtn_to_dot_serializer
        fprtn
        machine
        )

install(TARGETS fprtn_to_dot_serializer EXPORT fprtn_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT fprtn_to_dot_serializerConfig DESTINATION share/grapenlp/fprtn_to_dot_serializer/cmake COMPONENT libgrapenlpdev)
export(TARGETS fprtn_to_dot_serializer FILE fprtn_to_dot_serializerConfig.cmake)
