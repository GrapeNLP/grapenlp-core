project(to_canonical_form VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(to_canonical_form STATIC src/to_canonical_form.cpp)
target_include_directories(to_canonical_form PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(to_canonical_form text_delaf)

install(TARGETS to_canonical_form EXPORT to_canonical_formConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT to_canonical_formConfig DESTINATION share/grapenlp/to_canonical_form/cmake COMPONENT libgrapenlpdev)
export(TARGETS to_canonical_form FILE to_canonical_formConfig.cmake)

# Test files
add_executable(to_canonical_form_test test/to_canonical_form_test.cpp)
target_link_libraries(to_canonical_form_test
        to_canonical_form
        token
        )
