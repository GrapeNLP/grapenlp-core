project(output_fprtn_prune VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(output_fprtn_prune STATIC src/output_fprtn_prune.cpp)
target_include_directories(output_fprtn_prune PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn_prune
        output_fprtn
        output_fprtn_to_dot_serializer
        )

install(TARGETS output_fprtn_prune EXPORT output_fprtn_pruneConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT output_fprtn_pruneConfig DESTINATION share/grapenlp/output_fprtn_prune/cmake COMPONENT libgrapenlpdev)
export(TARGETS output_fprtn_prune FILE output_fprtn_pruneConfig.cmake)
