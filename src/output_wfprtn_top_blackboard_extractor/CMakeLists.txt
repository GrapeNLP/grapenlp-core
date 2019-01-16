project(output_wfprtn_top_blackboard_extractor VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(output_wfprtn_top_blackboard_extractor STATIC
        src/wfprtn_top_blackboard_extractor.cpp
        src/aw_fprtn_top_blackboard_extractor.cpp
        src/uaw_fprtn_top_blackboard_extractor.cpp
        src/luaw_fprtn_top_blackboard_extractor.cpp
        src/xw_fprtn_top_blackboard_extractor.cpp
        src/uxw_fprtn_top_blackboard_extractor.cpp
        src/luxw_fprtn_top_blackboard_extractor.cpp
        )
target_include_directories(output_wfprtn_top_blackboard_extractor PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_wfprtn_top_blackboard_extractor
        util
        machine
        output_fprtn_top
        )

install(TARGETS output_wfprtn_top_blackboard_extractor EXPORT output_wfprtn_top_blackboard_extractorConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT output_wfprtn_top_blackboard_extractorConfig DESTINATION share/grapenlp/output_wfprtn_top_blackboard_extractor/cmake COMPONENT libgrapenlpdev)
export(TARGETS output_wfprtn_top_blackboard_extractor FILE output_wfprtn_top_blackboard_extractorConfig.cmake)
