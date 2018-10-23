project(cgrapenlp VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_executable(cgrapenlp src/grapenlp.cpp)
SET_TARGET_PROPERTIES(cgrapenlp PROPERTIES OUTPUT_NAME grapenlp)
target_link_libraries(cgrapenlp
        grapenlp
        ${Boost_PROGRAM_OPTIONS_LIBRARY})

install(TARGETS cgrapenlp EXPORT cgrapenlpConfig
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT cgrapenlp)
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT cgrapenlpConfig DESTINATION share/cgrapenlp/cmake)
export(TARGETS cgrapenlp FILE cgrapenlpConfig.cmake)


#set(CPACK_DEB_COMPONENT_INSTALL ON)
#set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
#set(CPACK_GENERATOR "DEB")
#set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_NAME "libgrapenlp-dev")
#set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
#set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_ARCHITECTURE "amd64")
#set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_DEPENDS "libgrapenlp (>= 2.0.0), libboost-program-options-dev (<< 3.0.0)")
#set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Javier Sastre")
#set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "GRAPENLP library (Grammar Annotation Patterns Engine)")
#set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_SECTION "libs")
#set(CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_PRIORITY "optional")
#set(CPACK_DEBIAN_LIBGRAPENLP_FILE_NAME "libgrapenlp-${PROJECT_VERSION}-${CPACK_DEBIAN_LIBGRAPENLP_PACKAGE_ARCHITECTURE}.deb")
#include(CPack)
#cpack_add_component(libgrapenlp REQUIRED)