project(rtno_to_dot_serializer VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(rtno_to_dot_serializer STATIC src/rtno_to_dot_serializer.cpp)
target_include_directories(rtno_to_dot_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(rtno_to_dot_serializer rtno)

install(TARGETS rtno_to_dot_serializer EXPORT rtno_to_dot_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT rtno_to_dot_serializerConfig DESTINATION share/rtno_to_dot_serializer/cmake)
export(TARGETS rtno_to_dot_serializer FILE rtno_to_dot_serializerConfig.cmake)
