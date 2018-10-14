project(to_decompressed_canonical_form VERSION 0.1 LANGUAGES CXX)

add_library(to_decompressed_canonical_form STATIC src/to_decompressed_canonical_form.cpp)
target_include_directories(to_decompressed_canonical_form PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(to_decompressed_canonical_form compressed_delaf)

install(TARGETS to_decompressed_canonical_form EXPORT to_decompressed_canonical_formConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT to_decompressed_canonical_formConfig DESTINATION share/to_decompressed_canonical_form/cmake)
export(TARGETS to_decompressed_canonical_form FILE to_decompressed_canonical_formConfig.cmake)

# Test files
add_executable(to_decompressed_canonical_form_test test/to_decompressed_canonical_form_test.cpp)
target_link_libraries(to_decompressed_canonical_form_test
        to_decompressed_canonical_form
        token
        )
