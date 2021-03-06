#
# GRAPENLP
#
# Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
#
#
#
#
# @author Javier Sastre
#

project(unicode VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

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
		src/u_trie_with_ptr_data_reader.cpp
		src/u_trie_with_data_reader.cpp
		src/u_trie_reader.cpp
		src/u_trie_with_ptr_data.cpp
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
target_link_libraries(unicode
		util
		)

install(TARGETS unicode EXPORT unicodeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT unicodeConfig DESTINATION share/grapenlp/unicode/cmake COMPONENT libgrapenlpdev)
export(TARGETS unicode FILE unicodeConfig.cmake)

add_executable(dump_chars src/dump_chars.cpp)
target_link_libraries(dump_chars unicode)

# Test files
if (BUILD_TESTING)
	add_executable(test_case test/test_case.cpp)
	set_target_properties(test_case PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	target_link_libraries(test_case unicode)

	add_executable(u_trie_test test/u_trie_test.cpp)
	set_target_properties(u_trie_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
	target_link_libraries(u_trie_test unicode)
endif (BUILD_TESTING)
