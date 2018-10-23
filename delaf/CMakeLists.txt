project(delaf VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT delafConfig DESTINATION share/grapenlp/delaf/cmake COMPONENT libgrapenlpdev)
export(TARGETS delaf FILE delafConfig.cmake)
