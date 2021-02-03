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

project(lrb_tree VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(lrb_tree STATIC
        src/lrb_tree.cpp
        src/lrb_tree_set.cpp
        src/lrb_tree_multiset.cpp
        src/lrb_tree_map.cpp
        src/lrb_tree_multimap.cpp
        src/lrb_tree_set_3w.cpp
        src/lrb_tree_multiset_3w.cpp
        src/lrb_tree_map_3w.cpp
        src/lrb_tree_multimap_3w.cpp
        )
target_include_directories(lrb_tree PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(lrb_tree
        util
        )

install(TARGETS lrb_tree EXPORT lrb_treeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT lrb_treeConfig DESTINATION share/grapenlp/lrb_tree/cmake COMPONENT libgrapenlpdev)
export(TARGETS lrb_tree FILE lrb_treeConfig.cmake)

# Test files
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND BUILD_TESTING)
    add_executable(lrb_tree_set_test test/lrb_tree_set_test.cpp)
    set_target_properties(lrb_tree_set_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(lrb_tree_set_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(lrb_tree_map_test test/lrb_tree_map_test.cpp)
    set_target_properties(lrb_tree_map_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(lrb_tree_map_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(lrb_tree_multiset_test test/lrb_tree_multiset_test.cpp)
    set_target_properties(lrb_tree_multiset_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(lrb_tree_multiset_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(lrb_tree_multimap_test test/lrb_tree_multimap_test.cpp)
    set_target_properties(lrb_tree_multimap_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(lrb_tree_multimap_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )
endif (CMAKE_BUILD_TYPE STREQUAL "Debug" AND BUILD_TESTING)
#add_executable(lrb_tree_efficiency test/lrb_tree_efficiency.cpp)
#target_link_libraries(lrb_tree_efficiency
#        util
#        assoc_container_impl_selector
#        )
