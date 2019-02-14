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

project(output_fprtn_top VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(output_fprtn_top STATIC
        src/output_fprtn_top.cpp
        src/aw_output_fprtn_top.cpp
        src/uaw_output_fprtn_top.cpp
        src/luaw_output_fprtn_top.cpp
        src/xw_output_fprtn_top.cpp
        src/uxw_output_fprtn_top.cpp
        src/luxw_output_fprtn_top.cpp
        )

target_include_directories(output_fprtn_top PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

target_link_libraries(output_fprtn_top
        machine
        output_fprtn
        )

install(TARGETS output_fprtn_top EXPORT output_fprtn_topConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT output_fprtn_topConfig DESTINATION share/grapenlp/output_fprtn_top/cmake COMPONENT libgrapenlpdev)
export(TARGETS output_fprtn_top FILE output_fprtn_topConfig.cmake)
