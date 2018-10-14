project(delaf VERSION 0.1 LANGUAGES CXX)

add_library(delaf STATIC
        src/delaf_entry_filter_default_weight.cpp
        src/delaf_entry_filter_type.cpp
        src/u_delaf_constants.cpp
        src/u_delaf_entry_filter_codes.cpp
        )
target_include_directories(delaf PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(delaf unicode)

install(TARGETS delaf EXPORT delafConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT delafConfig DESTINATION share/delaf/cmake)
export(TARGETS delaf FILE delafConfig.cmake)
