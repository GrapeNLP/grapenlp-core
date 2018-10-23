project(compressed_delaf VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(compressed_delaf STATIC
        src/bin_delaf.cpp
        src/inf_delaf.cpp
        src/bin_delaf_reader.cpp
        src/inf_delaf_reader.cpp
        src/compressed_delaf_reader.cpp
        src/decompress_delaf_writer.cpp
        src/compressed_delaf_entry_filter.cpp
        src/compressed_delaf_entry_filter_factory.cpp
        )
target_include_directories(compressed_delaf PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

install(TARGETS compressed_delaf EXPORT compressed_delafConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT compressed_delafConfig DESTINATION share/compressed_delaf/cmake)
export(TARGETS compressed_delaf FILE compressed_delafConfig.cmake)

target_link_libraries(compressed_delaf delaf)

add_executable(cdump src/cdump.cpp)
target_link_libraries(cdump compressed_delaf)

add_executable(filter_compressed_delaf src/filter_compressed_delaf.cpp)
target_link_libraries(filter_compressed_delaf compressed_delaf)

#Test files
add_executable(test_compressed_delaf test/test_compressed_delaf.cpp)
target_link_libraries(test_compressed_delaf compressed_delaf)
