project(util VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT utilConfig DESTINATION share/grapenlp/util/cmake COMPONENT libgrapenlpdev)
export(TARGETS util FILE utilConfig.cmake)

# Test files
if (BUILD_TESTING)
	add_executable(ansi_text_attribute_test
		test/ansi_text_attribute_test.cpp)
	set_target_properties(ansi_text_attribute_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	target_link_libraries(ansi_text_attribute_test
		util
		gtest_main)

	add_test(NAME ansi_text_attribute_test COMMAND ansi_text_attribute_test)

	#add_executable(trie_test
	#		test/trie_test.cpp)
	#set_target_properties(trie_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	#target_link_libraries(trie_test
	#		util
	#		GTest::GTest GTest::Main)

	#add_test(trie_test trie_test)
endif (BUILD_TESTING)
