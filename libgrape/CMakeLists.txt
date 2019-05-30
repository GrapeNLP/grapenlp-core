project(libgrape VERSION $ENV{VERSION} LANGUAGES CXX)

add_library(grape SHARED src/ualxiw_manager.cpp)

target_include_directories(grape PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

target_link_libraries(grape
        manager
        )

install(TARGETS grape EXPORT grapeConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT libgrape)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT grapeConfig DESTINATION share/grape/cmake)
export(TARGETS grape FILE grapeConfig.cmake)


set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_LIBGRAPE_PACKAGE_NAME "libgrape")
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_LIBGRAPE_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_LIBGRAPE_PACKAGE_DEPENDS "libboost-program-options-dev (>= 1.58.0), libboost-program-options-dev (<< 2.0.0)")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Javier Sastre")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "GRAPE library (Grammar Annotation Patterns Engine)")
set(CPACK_DEBIAN_LIBGRAPE_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_LIBGRAPE_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_LIBGRAPE_FILE_NAME "libgrape-${PROJECT_VERSION}-${CPACK_DEBIAN_LIBGRAPE_PACKAGE_ARCHITECTURE}.deb")
include(CPack)
cpack_add_component(libgrape REQUIRED)

