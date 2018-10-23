project(out_serializer VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(out_serializer STATIC
        src/movistarbot_phone_digit_separator_set.cpp
        src/movistarbot_tag_dico.cpp
        src/movistarbot_out_serializer.cpp
        src/movistarbot_weighted_out_serializer.cpp
        )
target_include_directories(out_serializer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(out_serializer
        token
        segment
        unicode
        )

install(TARGETS out_serializer EXPORT out_serializerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT out_serializerConfig DESTINATION share/grapenlp/out_serializer/cmake COMPONENT libgrapenlpdev)
export(TARGETS out_serializer FILE out_serializerConfig.cmake)
