project(pcfgla VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT pcfglaConfig DESTINATION share/grapenlp/pcfgla/cmake COMPONENT libgrapenlpdev)
export(TARGETS pcfgla FILE pcfglaConfig.cmake)

# Test files
add_executable(test_reader test/test_reader.cpp)
target_link_libraries(test_reader pcfgla)