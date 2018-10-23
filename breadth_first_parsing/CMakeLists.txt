project(breadth_first_parsing VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(breadth_first_parsing STATIC
        src/breadth_first_parser.cpp
        src/breadth_first_parser_no_output.cpp
        src/lua_breadth_first_parser.cpp
        src/lua_breadth_first_parser_no_output.cpp
        src/luaw_breadth_first_parser.cpp
        src/luaw_breadth_first_parser_no_output.cpp
        src/lx_breadth_first_parser.cpp
        src/lx_breadth_first_parser_no_output.cpp
        src/lxw_breadth_first_parser.cpp
        src/lxw_breadth_first_parser_no_output.cpp
        )
target_include_directories(breadth_first_parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(breadth_first_parsing
        assoc_container_impl_selector
        rtno
        )

install(TARGETS breadth_first_parsing EXPORT breadth_first_parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT breadth_first_parsingConfig DESTINATION share/breadth_first_parsing/cmake)
export(TARGETS breadth_first_parsing FILE breadth_first_parsingConfig.cmake)
