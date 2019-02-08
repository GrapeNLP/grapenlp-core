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

project(output_wfprtn_top_blackboard_extractor VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(output_wfprtn_top_blackboard_extractor STATIC
        src/wfprtn_top_blackboard_extractor.cpp
        src/aw_fprtn_top_blackboard_extractor.cpp
        src/uaw_fprtn_top_blackboard_extractor.cpp
        src/luaw_fprtn_top_blackboard_extractor.cpp
        src/xw_fprtn_top_blackboard_extractor.cpp
        src/uxw_fprtn_top_blackboard_extractor.cpp
        src/luxw_fprtn_top_blackboard_extractor.cpp
        )
target_include_directories(output_wfprtn_top_blackboard_extractor PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_wfprtn_top_blackboard_extractor
        util
        machine
        output_fprtn_top
        )

install(TARGETS output_wfprtn_top_blackboard_extractor EXPORT output_wfprtn_top_blackboard_extractorConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT output_wfprtn_top_blackboard_extractorConfig DESTINATION share/grapenlp/output_wfprtn_top_blackboard_extractor/cmake COMPONENT libgrapenlpdev)
export(TARGETS output_wfprtn_top_blackboard_extractor FILE output_wfprtn_top_blackboard_extractorConfig.cmake)
