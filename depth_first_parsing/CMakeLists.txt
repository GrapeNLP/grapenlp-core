project(depth_first_parsing VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(depth_first_parsing STATIC
        src/depth_first_parser.cpp
        src/depth_first_parser_no_output.cpp
        src/lua_depth_first_parser.cpp
        src/lua_depth_first_parser_no_output.cpp
        src/luaw_depth_first_parser.cpp
        src/luaw_depth_first_parser_no_output.cpp
        src/lx_depth_first_parser.cpp
        src/lx_depth_first_parser_no_output.cpp
        src/lxw_depth_first_parser.cpp
        src/lxw_depth_first_parser_no_output.cpp
        )
target_include_directories(depth_first_parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(depth_first_parsing
        assoc_container_impl_selector
        rtno
        )

install(TARGETS depth_first_parsing EXPORT depth_first_parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT depth_first_parsingConfig DESTINATION share/grapenlp/depth_first_parsing/cmake COMPONENT libgrapenlpdev)
export(TARGETS depth_first_parsing FILE depth_first_parsingConfig.cmake)
