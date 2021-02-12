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

project(pcfgla_to_rtno VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(pcfgla_to_rtno STATIC src/pcfgla_to_rtno.cpp)
target_include_directories(pcfgla_to_rtno PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(pcfgla_to_rtno
        pcfgla
        rtno
        )

install(TARGETS pcfgla_to_rtno EXPORT pcfgla_to_rtnoConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT pcfgla_to_rtnoConfig DESTINATION share/grapenlp/pcfgla_to_rtno/cmake COMPONENT libgrapenlpdev)
export(TARGETS pcfgla_to_rtno FILE pcfgla_to_rtnoConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(test_converter test/test_converter.cpp)
    set_target_properties(test_converter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_converter
            pcfgla_to_rtno
            rtno_to_dot_serializer
            )
endif (BUILD_TESTING)
