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

project(context VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(context STATIC
        src/context.cpp
        src/context_key_value_hasher.cpp
        src/u_context.cpp
        src/u_context_key_value_hasher.cpp
        src/u_context_reader.cpp
        )
target_include_directories(context PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(context
        unicode
        )

install(TARGETS context EXPORT contextConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT contextConfig DESTINATION share/grapenlp/context/cmake COMPONENT libgrapenlpdev)
export(TARGETS context FILE contextConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(test_u_context
            test/test_u_context.cpp)
    set_target_properties(test_u_context PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_u_context
            context
            gtest_main)

    add_test(NAME test_u_context COMMAND test_u_context)
endif (BUILD_TESTING)
