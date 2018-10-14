project(fst VERSION 0.1 LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT fstConfig DESTINATION share/fst/cmake)
export(TARGETS fst FILE fstConfig.cmake)
