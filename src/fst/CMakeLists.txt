project(fst VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(fst STATIC
        src/fst.cpp
        src/u_fst.cpp
        )
target_include_directories(fst PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(fst unicode)

install(TARGETS fst EXPORT fstConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT fstConfig DESTINATION share/grapenlp/fst/cmake COMPONENT libgrapenlpdev)
export(TARGETS fst FILE fstConfig.cmake)
