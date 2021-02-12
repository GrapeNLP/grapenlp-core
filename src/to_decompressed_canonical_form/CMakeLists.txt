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

project(to_decompressed_canonical_form VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(to_decompressed_canonical_form STATIC src/to_decompressed_canonical_form.cpp)
target_include_directories(to_decompressed_canonical_form PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(to_decompressed_canonical_form
        compressed_delaf
        )

install(TARGETS to_decompressed_canonical_form EXPORT to_decompressed_canonical_formConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT to_decompressed_canonical_formConfig DESTINATION share/grapenlp/to_decompressed_canonical_form/cmake COMPONENT libgrapenlpdev)
export(TARGETS to_decompressed_canonical_form FILE to_decompressed_canonical_formConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(to_decompressed_canonical_form_test test/to_decompressed_canonical_form_test.cpp)
    set_target_properties(to_decompressed_canonical_form_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(to_decompressed_canonical_form_test
            to_decompressed_canonical_form
            token
            )
endif (BUILD_TESTING)
