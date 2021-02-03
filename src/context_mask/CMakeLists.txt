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

project(context_mask VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(context_mask STATIC
        src/context_mask.cpp
        src/u_context_mask.cpp
        src/u_context_mask_factory.cpp
        )
target_include_directories(context_mask PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(context_mask
        context
        )

install(TARGETS context_mask EXPORT context_maskConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT context_maskConfig DESTINATION share/grapenlp/context_mask/cmake COMPONENT libgrapenlpdev)
export(TARGETS context_mask FILE context_maskConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(test_u_context_mask_factory
            test/test_u_context_mask_factory.cpp)
    set_target_properties(test_u_context_mask_factory PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_u_context_mask_factory
            context_mask
            gtest_main)

    add_test(NAME test_u_context_mask_factory COMMAND test_u_context_mask_factory)
endif (BUILD_TESTING)
