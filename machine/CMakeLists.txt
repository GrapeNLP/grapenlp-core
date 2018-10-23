project(machine VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(machine STATIC
        src/tag_input_traits.cpp
        src/tag_reader_traits.cpp
        src/tag_serializer_traits.cpp
        src/weight_traits.cpp
        src/weighted_tag_output_traits.cpp
        )
target_include_directories(machine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(machine util)

install(TARGETS machine EXPORT machineConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT machineConfig DESTINATION share/machine/cmake)
export(TARGETS machine FILE machineConfig.cmake)
