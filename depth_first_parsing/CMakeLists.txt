project(depth_first_parsing VERSION 0.1 LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT depth_first_parsingConfig DESTINATION share/depth_first_parsing/cmake)
export(TARGETS depth_first_parsing FILE depth_first_parsingConfig.cmake)
