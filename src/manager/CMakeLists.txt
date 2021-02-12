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

project(manager VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(manager STATIC
        src/ul_manager.cpp
        )
target_include_directories(manager PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(manager
        fst2_reader
        rtno_to_dot_serializer
        common_parsing
        breadth_first_parsing
        earley_parsing
        to_fprtn_parsing
        output_fprtn_prune
        to_fprtn_zpps_parsing
        output_fprtn_zpps_prune
        to_fprtn_top_parsing
        output_fprtn_top_prune
        depth_first_parsing
        output_fprtn_breadth_first_expander
        output_fprtn_blackboard_set_expander
        output_wfprtn_top_blackboard_extractor
        context
        out_serializer
        to_canonical_form
        to_decompressed_canonical_form
        )

install(TARGETS manager EXPORT managerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT managerConfig DESTINATION share/grapenlp/manager/cmake COMPONENT libgrapenlpdev)
export(TARGETS manager FILE managerConfig.cmake)
