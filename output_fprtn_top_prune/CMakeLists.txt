project(output_fprtn_top_prune VERSION 0.1 LANGUAGES CXX)

add_library(output_fprtn_top_prune STATIC
        src/output_fprtn_top_prune.cpp
        src/aw_output_fprtn_top_prune.cpp
        src/uaw_output_fprtn_top_prune.cpp
        src/luaw_output_fprtn_top_prune.cpp
        src/xw_output_fprtn_top_prune.cpp
        src/uxw_output_fprtn_top_prune.cpp
        src/luxw_output_fprtn_top_prune.cpp
        )
target_include_directories(output_fprtn_top_prune PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn_top_prune
        output_fprtn_top
        output_fprtn_prune
        output_fprtn_to_dot_serializer
        )

install(TARGETS output_fprtn_top_prune EXPORT output_fprtn_top_pruneConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT output_fprtn_top_pruneConfig DESTINATION share/output_fprtn_top_prune/cmake)
export(TARGETS output_fprtn_top_prune FILE output_fprtn_top_pruneConfig.cmake)
