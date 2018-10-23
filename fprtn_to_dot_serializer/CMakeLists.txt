project(fprtn_to_dot_serializer VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(fprtn_to_dot_serializer STATIC
        src/fprtn_to_dot_serializer.cpp
        src/inv_fprtn_to_dot_serializer.cpp
        )
target_include_directories(fprtn_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(fprtn_to_dot_serializer
        fprtn
        machine
        )

install(TARGETS fprtn_to_dot_serializer EXPORT fprtn_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT fprtn_to_dot_serializerConfig DESTINATION share/fprtn_to_dot_serializer/cmake)
export(TARGETS fprtn_to_dot_serializer FILE fprtn_to_dot_serializerConfig.cmake)
