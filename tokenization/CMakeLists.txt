project(tokenization VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(token STATIC
        src/token.cpp
        src/tokenization.cpp
        )
target_include_directories(token PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(token unicode)

install(TARGETS token EXPORT tokenConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT tokenConfig DESTINATION share/grapenlp/token/cmake COMPONENT libgrapenlpdev)
export(TARGETS token FILE tokenConfig.cmake)

add_executable(tokenize src/tokenize.cpp)
target_link_libraries(tokenize token)