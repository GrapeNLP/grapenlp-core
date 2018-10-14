project(rb_tree_to_dot_serializer VERSION 0.1 LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT rb_tree_to_dot_serializerConfig DESTINATION share/rb_tree_to_dot_serializer/cmake)
export(TARGETS rb_tree_to_dot_serializer FILE rb_tree_to_dot_serializerConfig.cmake)
