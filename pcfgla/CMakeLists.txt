project(pcfgla VERSION 0.1 LANGUAGES CXX)

add_library(pcfgla STATIC
        src/pcfgla.cpp
        src/pcfgla_constants.cpp
        src/pcfgla_reader.cpp
        )
target_include_directories(pcfgla PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(pcfgla
        lrb_tree
        unicode
        )

install(TARGETS pcfgla EXPORT pcfglaConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT pcfglaConfig DESTINATION share/pcfgla/cmake)
export(TARGETS pcfgla FILE pcfglaConfig.cmake)

# Test files
add_executable(test_reader test/test_reader.cpp)
target_link_libraries(test_reader pcfgla)