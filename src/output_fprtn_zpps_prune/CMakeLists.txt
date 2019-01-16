project(output_fprtn_zpps_prune VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(output_fprtn_zpps_prune STATIC
        src/output_fprtn_zpps_prune.cpp
        src/a_output_fprtn_zpps_prune.cpp
        src/ua_output_fprtn_zpps_prune.cpp
        src/lua_output_fprtn_zpps_prune.cpp
        src/aw_output_fprtn_zpps_prune.cpp
        src/uaw_output_fprtn_zpps_prune.cpp
        src/luaw_output_fprtn_zpps_prune.cpp
        src/x_output_fprtn_zpps_prune.cpp
        src/xw_output_fprtn_zpps_prune.cpp
        src/ux_output_fprtn_zpps_prune.cpp
        src/lux_output_fprtn_zpps_prune.cpp
        src/uxw_output_fprtn_zpps_prune.cpp
        src/luxw_output_fprtn_zpps_prune.cpp
        )

target_include_directories(output_fprtn_zpps_prune PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

target_link_libraries(output_fprtn_zpps_prune
        output_fprtn_zpps
        output_fprtn_prune
        output_fprtn_to_dot_serializer
        )

install(TARGETS output_fprtn_zpps_prune EXPORT output_fprtn_zpps_pruneConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT output_fprtn_zpps_pruneConfig DESTINATION share/grapenlp/output_fprtn_zpps_prune/cmake COMPONENT libgrapenlpdev)
export(TARGETS output_fprtn_zpps_prune FILE output_fprtn_zpps_pruneConfig.cmake)
