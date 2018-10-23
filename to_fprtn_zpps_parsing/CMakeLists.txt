project(to_fprtn_zpps_parsing VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(to_fprtn_zpps_parsing STATIC
        src/to_fprtn_zpps_parser.cpp
        src/lua_to_fprtn_zpps_parser.cpp
        src/luaw_to_fprtn_zpps_parser.cpp
        src/lx_to_fprtn_zpps_parser.cpp
        src/lxw_to_fprtn_zpps_parser.cpp
        )
target_include_directories(to_fprtn_zpps_parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(to_fprtn_zpps_parsing
        rtno
        output_fprtn_zpps_prune
        )

install(TARGETS to_fprtn_zpps_parsing EXPORT to_fprtn_zpps_parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT to_fprtn_zpps_parsingConfig DESTINATION share/to_fprtn_zpps_parsing/cmake)
export(TARGETS to_fprtn_zpps_parsing FILE to_fprtn_zpps_parsingConfig.cmake)
