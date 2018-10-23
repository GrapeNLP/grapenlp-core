project(lrb_tree VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

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
target_link_libraries(lrb_tree util)

install(TARGETS lrb_tree EXPORT lrb_treeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT lrb_treeConfig DESTINATION share/lrb_tree/cmake)
export(TARGETS lrb_tree FILE lrb_treeConfig.cmake)

# Test files
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(lrb_tree_set_test test/lrb_tree_set_test.cpp)
    target_link_libraries(lrb_tree_set_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(lrb_tree_map_test test/lrb_tree_map_test.cpp)
    target_link_libraries(lrb_tree_map_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(lrb_tree_multiset_test test/lrb_tree_multiset_test.cpp)
    target_link_libraries(lrb_tree_multiset_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )

    add_executable(lrb_tree_multimap_test test/lrb_tree_multimap_test.cpp)
    target_link_libraries(lrb_tree_multimap_test
            util
            lrb_tree_to_dot_serializer
            ${Boost_PROGRAM_OPTIONS_LIBRARY}
            )
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
#add_executable(lrb_tree_efficiency test/lrb_tree_efficiency.cpp)
#target_link_libraries(lrb_tree_efficiency
#        util
#        assoc_container_impl_selector
#        )
