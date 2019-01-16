project(output_fprtn_zpps VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(output_fprtn_zpps STATIC
        src/output_fprtn_zpps.cpp
        src/a_output_fprtn_zpps.cpp
        src/ua_output_fprtn_zpps.cpp
        src/lua_output_fprtn_zpps.cpp
        src/aw_output_fprtn_zpps.cpp
        src/uaw_output_fprtn_zpps.cpp
        src/luaw_output_fprtn_zpps.cpp
        src/x_output_fprtn_zpps.cpp
        src/xw_output_fprtn_zpps.cpp
        src/ux_output_fprtn_zpps.cpp
        src/lux_output_fprtn_zpps.cpp
        src/uxw_output_fprtn_zpps.cpp
        src/luxw_output_fprtn_zpps.cpp
        )
target_include_directories(output_fprtn_zpps PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn_zpps output_fprtn)

install(TARGETS output_fprtn_zpps EXPORT output_fprtn_zppsConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT output_fprtn_zppsConfig DESTINATION share/grapenlp/output_fprtn_zpps/cmake COMPONENT libgrapenlpdev)
export(TARGETS output_fprtn_zpps FILE output_fprtn_zppsConfig.cmake)
