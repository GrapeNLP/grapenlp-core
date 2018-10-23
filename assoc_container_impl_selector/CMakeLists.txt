project(assoc_container_impl_selector VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(assoc_container_impl_selector STATIC
        src/set_impl_selector.cpp
        src/map_impl_selector.cpp
        src/multiset_impl_selector.cpp
        src/multimap_impl_selector.cpp)
target_include_directories(assoc_container_impl_selector PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(assoc_container_impl_selector lrb_tree)

install(TARGETS assoc_container_impl_selector EXPORT assoc_container_impl_selectorConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT assoc_container_impl_selectorConfig DESTINATION share/grapenlp/assoc_container_impl_selector/cmake COMPONENT libgrapenlpdev)
export(TARGETS assoc_container_impl_selector FILE assoc_container_impl_selectorConfig.cmake)