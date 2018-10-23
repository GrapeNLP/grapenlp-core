project(text_delaf VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(text_delaf STATIC
        src/text_delaf.cpp
        src/u_text_delaf_reader.cpp
        src/u_text_delaf_writer.cpp
        src/text_delaf_entry_filter.cpp
        src/u_text_delaf_entry_filter.cpp
        src/u_text_delaf_entry_filter_factory.cpp
        )
target_include_directories(text_delaf PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(text_delaf delaf)

install(TARGETS text_delaf EXPORT text_delafConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT text_delafConfig DESTINATION share/text_delaf/cmake)
export(TARGETS text_delaf FILE text_delafConfig.cmake)

add_executable(normalize_delaf src/normalize_delaf.cpp)
target_link_libraries(normalize_delaf text_delaf)

add_executable(dump src/dump.cpp)
target_link_libraries(dump text_delaf)

add_executable(dump_lemmas src/dump_lemmas.cpp)
target_link_libraries(dump_lemmas text_delaf)

add_executable(dump_ppooss src/dump_ppooss.cpp)
target_link_libraries(dump_ppooss text_delaf)

add_executable(dump_semantic_traits src/dump_semantic_traits.cpp)
target_link_libraries(dump_semantic_traits text_delaf)

add_executable(dump_flexional_traits src/dump_flexional_traits.cpp)
target_link_libraries(dump_flexional_traits text_delaf)

add_executable(dump_clitic_pronouns src/dump_clitic_pronouns.cpp)
target_link_libraries(dump_clitic_pronouns text_delaf)

add_executable(filter_delaf src/filter_delaf.cpp)
target_link_libraries(filter_delaf text_delaf)

add_executable(edit_semantic_traits src/edit_semantic_traits.cpp)
target_link_libraries(edit_semantic_traits text_delaf)
