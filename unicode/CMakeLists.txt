project(unicode VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(unicode STATIC
		src/error.cpp
		src/u_array_const_ref_x_weight.cpp
		src/u_array.cpp
		src/u_list_reader.cpp
		src/u_list.cpp
		src/u_lowercase_table.cpp
		src/u_set_reader.cpp
		src/u_set_trie_reader.cpp
		src/u_set_trie.cpp
		src/u_set.cpp
		src/u_tolowercase_table.cpp
		src/u_touppercase_table.cpp
		src/u_trie_reader.cpp
		src/u_trie.cpp
		src/u_uppercase_table.cpp
		src/u_vector_reader.cpp
		src/u_vector.cpp
		src/unsigned_int_char_traits.cpp
		src/unichar.cpp
		src/unicode.cpp
		)
target_include_directories(unicode PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
		PRIVATE src)
target_link_libraries(unicode util)

install(TARGETS unicode EXPORT unicodeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT unicodeConfig DESTINATION share/grapenlp/unicode/cmake COMPONENT libgrapenlpdev)
export(TARGETS unicode FILE unicodeConfig.cmake)

add_executable(dump_chars src/dump_chars.cpp)
target_link_libraries(dump_chars unicode)

# Test files
add_executable(test_case test/test_case.cpp)
target_link_libraries(test_case unicode)

add_executable(u_trie_test test/u_trie_test.cpp)
target_link_libraries(u_trie_test unicode)
