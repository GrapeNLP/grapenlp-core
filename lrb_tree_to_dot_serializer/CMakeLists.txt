project(lrb_tree_to_dot_serializer VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(lrb_tree_to_dot_serializer STATIC
        src/lrb_tree_to_dot_serializer.cpp
        )
target_include_directories(lrb_tree_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(lrb_tree_to_dot_serializer
        lrb_tree
        machine
        )

install(TARGETS lrb_tree_to_dot_serializer EXPORT lrb_tree_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT lrb_tree_to_dot_serializerConfig DESTINATION share/grapenlp/lrb_tree_to_dot_serializer/cmake COMPONENT libgrapenlpdev)
export(TARGETS lrb_tree_to_dot_serializer FILE lrb_tree_to_dot_serializerConfig.cmake)
