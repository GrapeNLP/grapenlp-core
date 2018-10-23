project(util VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(util STATIC
        src/algorithm.cpp
        src/array_const_ref_x_weight.cpp
        src/array.cpp
        src/counter.cpp
        src/file.cpp
        src/functional.cpp
        src/iostream.cpp
        src/iterator_wrapper.cpp
        src/list.cpp
        src/map.cpp
        src/memory.cpp
        src/mtrace.cpp
        src/normalizer_iterator.cpp
        src/pool.cpp
        src/pool_sequence_x_weight.cpp
        src/set.cpp
        src/set_trie.cpp
        src/stats.cpp
        src/string.cpp
        src/trie.cpp
        src/trie_string_const_ref_x_weight.cpp
        src/vector.cpp)

target_include_directories(util PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

install(TARGETS util EXPORT utilConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT libgrapenlp-dev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT utilConfig DESTINATION share/util/cmake)
export(TARGETS util FILE utilConfig.cmake)

# Test files
#add_executable(ansi_text_attribute_test
#    test/ansi_text_attribute_test.cpp)

#target_link_libraries(ansi_text_attribute_test
#    util
#	GTest::GTest
#	GTest::Main)

#add_test(ansi_text_attribute_test ansi_text_attribute_test)

#add_executable(trie_test
#		test/trie_test.cpp)

#target_link_libraries(trie_test
#		util
#		GTest::GTest GTest::Main)

#add_test(trie_test trie_test)
