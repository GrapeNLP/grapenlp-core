project(output_fprtn_to_dot_serializer VERSION 0.1 LANGUAGES CXX)

add_library(output_fprtn_to_dot_serializer STATIC
        src/output_fprtn_to_dot_serializer.cpp
        src/inv_output_fprtn_to_dot_serializer.cpp
        )
target_include_directories(output_fprtn_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn_to_dot_serializer
        output_fprtn
        machine
        )

install(TARGETS output_fprtn_to_dot_serializer EXPORT output_fprtn_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT output_fprtn_to_dot_serializerConfig DESTINATION share/output_fprtn_to_dot_serializer/cmake)
export(TARGETS output_fprtn_to_dot_serializer FILE output_fprtn_to_dot_serializerConfig.cmake)
