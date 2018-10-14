project(parsing VERSION 0.1 LANGUAGES CXX)

add_library(parsing STATIC src/parser.cpp)
target_include_directories(parsing PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(parsing rtno)

install(TARGETS parsing EXPORT parsingConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT parsingConfig DESTINATION share/parsing/cmake)
export(TARGETS parsing FILE parsingConfig.cmake)
