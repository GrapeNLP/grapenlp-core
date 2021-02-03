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

project(rb_tree VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(rb_tree STATIC
        src/rb_tree.cpp
        src/rb_tree_set.cpp
        src/rb_tree_multiset.cpp
        src/rb_tree_map.cpp
        src/rb_tree_multimap.cpp
        src/rb_tree_set_3w.cpp
        src/rb_tree_multiset_3w.cpp
        src/rb_tree_map_3w.cpp
        src/rb_tree_multimap_3w.cpp
        )
target_include_directories(rb_tree PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(rb_tree
        util
        )

install(TARGETS rb_tree EXPORT rb_treeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT rb_treeConfig DESTINATION share/grapenlp/rb_tree/cmake COMPONENT libgrapenlpdev)
export(TARGETS rb_tree FILE rb_treeConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(rb_tree_set_test test/rb_tree_set_test.cpp)
    set_target_properties(rb_tree_set_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(rb_tree_set_test
            util
            rb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(rb_tree_map_test test/rb_tree_map_test.cpp)
    set_target_properties(rb_tree_map_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(rb_tree_map_test
            util
            rb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(rb_tree_multiset_test test/rb_tree_multiset_test.cpp)
    set_target_properties(rb_tree_multiset_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(rb_tree_multiset_test
            util
            rb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(rb_tree_multimap_test test/rb_tree_multimap_test.cpp)
    set_target_properties(rb_tree_multimap_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(rb_tree_multimap_test
            util
            rb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )
endif (BUILD_TESTING)
