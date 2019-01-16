project(rb_tree_to_dot_serializer VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(rb_tree_to_dot_serializer STATIC src/rb_tree_to_dot_serializer.cpp)
target_include_directories(rb_tree_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(rb_tree_to_dot_serializer
        rb_tree
        machine
        )

install(TARGETS rb_tree_to_dot_serializer EXPORT rb_tree_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT rb_tree_to_dot_serializerConfig DESTINATION share/grapenlp/rb_tree_to_dot_serializer/cmake COMPONENT libgrapenlpdev)
export(TARGETS rb_tree_to_dot_serializer FILE rb_tree_to_dot_serializerConfig.cmake)
