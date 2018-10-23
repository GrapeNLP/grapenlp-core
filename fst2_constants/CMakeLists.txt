project(fst2_constants VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(fst2_constants INTERFACE)
target_include_directories(fst2_constants INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS fst2_constants EXPORT fst2_constantsConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT fst2_constantsConfig DESTINATION share/grapenlp/fst2_constants/cmake COMPONENT libgrapenlpdev)
export(TARGETS fst2_constants FILE fst2_constantsConfig.cmake)
