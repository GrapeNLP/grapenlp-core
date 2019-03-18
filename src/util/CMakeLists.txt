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
		src/trie_perfect_hasher.cpp
		src/trie_with_data.cpp
		src/trie_with_def_data.cpp
		src/trie_with_ptr_data.cpp
        src/trie_string_const_ref_x_weight.cpp
        src/vector.cpp)

target_include_directories(util PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

install(TARGETS util EXPORT utilConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT utilConfig DESTINATION share/grapenlp/util/cmake COMPONENT libgrapenlpdev)
export(TARGETS util FILE utilConfig.cmake)

# Test files
if (BUILD_TESTING)
	add_executable(test_ansi_text_attribute
		test/test_ansi_text_attribute.cpp)
	set_target_properties(test_ansi_text_attribute PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	target_link_libraries(test_ansi_text_attribute
		util
		gtest_main)
	add_test(NAME test_ansi_text_attribute COMMAND test_ansi_text_attribute)

	add_executable(test_array
			test/test_array.cpp)
	set_target_properties(test_array PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	target_link_libraries(test_array
			util
			gtest_main)
	add_test(NAME test_array COMMAND test_array)

	add_executable(test_trie_perfect_hasher
			test/test_trie_perfect_hasher.cpp)
	set_target_properties(test_trie_perfect_hasher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	target_link_libraries(test_trie_perfect_hasher
			util
			gtest_main)
	add_test(NAME test_trie_perfect_hasher COMMAND test_trie_perfect_hasher)

	#add_executable(trie_test
	#		test/trie_test.cpp)
	#set_target_properties(trie_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	#target_link_libraries(trie_test
	#		util
	#		GTest::GTest GTest::Main)

	#add_test(trie_test trie_test)
endif (BUILD_TESTING)
