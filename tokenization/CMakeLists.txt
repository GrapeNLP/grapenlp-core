project(tokenization VERSION 0.1 LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT tokenConfig DESTINATION share/token/cmake)
export(TARGETS token FILE tokenConfig.cmake)

add_executable(tokenize src/tokenize.cpp)
target_link_libraries(tokenize token)