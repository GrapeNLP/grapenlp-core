project(manager VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(manager STATIC
        src/ul_manager.cpp
        )
target_include_directories(manager PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(manager
        fst2_reader
        rtno_to_dot_serializer
        parsing
        breadth_first_parsing
        earley_parsing
        to_fprtn_parsing
        output_fprtn_prune
        to_fprtn_zpps_parsing
        output_fprtn_zpps_prune
        to_fprtn_top_parsing
        output_fprtn_top_prune
        depth_first_parsing
        output_fprtn_breadth_first_expander
        output_fprtn_blackboard_set_expander
        output_wfprtn_top_blackboard_extractor
        out_serializer
        to_canonical_form
        to_decompressed_canonical_form
        )

install(TARGETS manager EXPORT managerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT managerConfig DESTINATION share/grapenlp/manager/cmake COMPONENT libgrapenlpdev)
export(TARGETS manager FILE managerConfig.cmake)
