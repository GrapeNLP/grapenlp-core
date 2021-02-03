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

project(text_delaf VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

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
target_link_libraries(text_delaf
        delaf
        )

install(TARGETS text_delaf EXPORT text_delafConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT text_delafConfig DESTINATION share/grapenlp/text_delaf/cmake COMPONENT libgrapenlpdev)
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
