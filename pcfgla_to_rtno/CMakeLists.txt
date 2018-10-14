project(pcfgla_to_rtno VERSION 0.1 LANGUAGES CXX)

add_library(pcfgla_to_rtno STATIC src/pcfgla_to_rtno.cpp)
target_include_directories(pcfgla_to_rtno PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(pcfgla_to_rtno
        pcfgla
        rtno
        )

install(TARGETS pcfgla_to_rtno EXPORT pcfgla_to_rtnoConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT pcfgla_to_rtnoConfig DESTINATION share/pcfgla_to_rtno/cmake)
export(TARGETS pcfgla_to_rtno FILE pcfgla_to_rtnoConfig.cmake)

# Test files
add_executable(test_converter test/test_converter.cpp)
target_link_libraries(test_converter
        pcfgla_to_rtno
        rtno_to_dot_serializer
        )
