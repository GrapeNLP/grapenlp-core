project(fst2_constants VERSION 0.1 LANGUAGES CXX)

add_library(fst2_constants INTERFACE)
target_include_directories(fst2_constants INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS fst2_constants EXPORT fst2_constantsConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT fst2_constantsConfig DESTINATION share/fst2_constants/cmake)
export(TARGETS fst2_constants FILE fst2_constantsConfig.cmake)
