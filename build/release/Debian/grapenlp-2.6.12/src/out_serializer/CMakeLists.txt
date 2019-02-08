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

project(out_serializer VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(out_serializer STATIC
        src/movistarbot_phone_digit_separator_set.cpp
        src/movistarbot_tag_dico.cpp
        src/movistarbot_out_serializer.cpp
        src/movistarbot_weighted_out_serializer.cpp
        )
target_include_directories(out_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(out_serializer
        token
        segment
        unicode
        )

install(TARGETS out_serializer EXPORT out_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT out_serializerConfig DESTINATION share/grapenlp/out_serializer/cmake COMPONENT libgrapenlpdev)
export(TARGETS out_serializer FILE out_serializerConfig.cmake)
