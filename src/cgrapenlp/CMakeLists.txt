project(cgrapenlp VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_executable(cgrapenlp src/grapenlp.cpp)
SET_TARGET_PROPERTIES(cgrapenlp PROPERTIES OUTPUT_NAME grapenlp)
target_link_libraries(cgrapenlp
        grapenlp
        ${Boost_PROGRAM_OPTIONS_LIBRARY})

install(TARGETS cgrapenlp EXPORT cgrapenlpConfig
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT cgrapenlp)
install(FILES "${CMAKE_BINARY_DIR}/debian/copyright"
        "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/grapenlp"
        COMPONENT cgrapenlp)
install(EXPORT cgrapenlpConfig DESTINATION share/grapenlp/grapenlp/cmake COMPONENT libgrapenlpdev)
export(TARGETS cgrapenlp FILE cgrapenlpConfig.cmake)
