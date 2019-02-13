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

project(pcfgla VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(pcfgla STATIC
        src/pcfgla.cpp
        src/pcfgla_constants.cpp
        src/pcfgla_reader.cpp
        )
target_include_directories(pcfgla PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(pcfgla
        lrb_tree
        unicode
        )

install(TARGETS pcfgla EXPORT pcfglaConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT pcfglaConfig DESTINATION share/grapenlp/pcfgla/cmake COMPONENT libgrapenlpdev)
export(TARGETS pcfgla FILE pcfglaConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(pcfgla_test_reader test/test_pcfgla_reader.cpp)
    set_target_properties(pcfgla_test_reader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(pcfgla_test_reader pcfgla)
endif (BUILD_TESTING)
