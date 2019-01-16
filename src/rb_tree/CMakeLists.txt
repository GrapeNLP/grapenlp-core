project(rb_tree VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

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
target_link_libraries(rb_tree util)

install(TARGETS rb_tree EXPORT rb_treeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT rb_treeConfig DESTINATION share/grapenlp/rb_tree/cmake COMPONENT libgrapenlpdev)
export(TARGETS rb_tree FILE rb_treeConfig.cmake)

# Test files
add_executable(rb_tree_set_test test/rb_tree_set_test.cpp)
target_link_libraries(rb_tree_set_test
        util
        rb_tree_to_dot_serializer
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

add_executable(rb_tree_map_test test/rb_tree_map_test.cpp)
target_link_libraries(rb_tree_map_test
        util
        rb_tree_to_dot_serializer
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

add_executable(rb_tree_multiset_test test/rb_tree_multiset_test.cpp)
target_link_libraries(rb_tree_multiset_test
        util
        rb_tree_to_dot_serializer
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

add_executable(rb_tree_multimap_test test/rb_tree_multimap_test.cpp)
target_link_libraries(rb_tree_multimap_test
        util
        rb_tree_to_dot_serializer
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )
