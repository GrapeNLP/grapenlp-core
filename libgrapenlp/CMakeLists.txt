project(libgrapenlp VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(grapenlp SHARED src/ualxiw_manager.cpp)

target_include_directories(grapenlp PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

target_link_libraries(grapenlp
        manager
        )

install(TARGETS grapenlp EXPORT grapenlpConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT libgrapenlp)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT grapenlpConfig DESTINATION share/grapenlp/cmake)
export(TARGETS grapenlp FILE grapenlpConfig.cmake)
