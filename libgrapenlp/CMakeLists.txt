project(libgrapenlp VERSION 1.0.0 LANGUAGES CXX)

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


set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_NAME "libgrapenlp")
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_DEPENDS "libboost-program-options-dev (>= 1.58.0), libboost-program-options-dev (<< 2.0.0)")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Javier Sastre")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "GRAPENLP library (Grammar Annotation Patterns Engine)")
set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_LIBGRAPENLP_FILE_NAME "libgrapenlp-${PROJECT_VERSION}-${CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_ARCHITECTURE}.deb")
include(CPack)
cpack_add_component(libgrapenlp REQUIRED)
