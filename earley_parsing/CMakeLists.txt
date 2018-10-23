project(earley_parsing VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(earley_parsing STATIC
        src/earley_parser.cpp
        src/earley_parser_no_output.cpp
        src/lua_earley_parser.cpp
        src/lua_earley_parser_no_output.cpp
        src/luaw_earley_parser.cpp
        src/luaw_earley_parser_no_output.cpp
        src/lx_earley_parser.cpp
        src/lx_earley_parser_no_output.cpp
        src/lxw_earley_parser.cpp
        src/lx_earley_parser_no_output.cpp
        )
target_include_directories(earley_parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(earley_parsing
        assoc_container_impl_selector
        rtno
        )

install(TARGETS earley_parsing EXPORT earley_parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT earley_parsingConfig DESTINATION share/grapenlp/earley_parsing/cmake COMPONENT libgrapenlpdev)
export(TARGETS earley_parsing FILE earley_parsingConfig.cmake)
