project(segment VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(segment STATIC
        src/out_bound.cpp
        src/u_out_bound.cpp
        src/out_bound_const_ref_x_weight.cpp
        src/u_out_bound_const_ref_x_weight.cpp
        src/segment.cpp
        src/segment_map_x_weight.cpp
        src/simple_segment.cpp
        src/simple_segment_array_x_weight.cpp
        )
target_include_directories(segment PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(segment
        assoc_container_impl_selector
        token
        )

install(TARGETS segment EXPORT segmentConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT segmentConfig DESTINATION share/grapenlp/segment/cmake COMPONENT libgrapenlpdev)
export(TARGETS segment FILE segmentConfig.cmake)
