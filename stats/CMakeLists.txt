project(stats VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(stats STATIC src/stats.cpp)
target_include_directories(stats PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(stats
        unicode
        util
        )

install(TARGETS stats EXPORT statsConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT statsConfig DESTINATION share/grapenlp/stats/cmake COMPONENT libgrapenlpdev)
export(TARGETS stats FILE statsConfig.cmake)
