#
# GRAPENLP
#
# Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

project(to_canonical_form VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(to_canonical_form STATIC src/to_canonical_form.cpp)
target_include_directories(to_canonical_form PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(to_canonical_form
        text_delaf
        )

install(TARGETS to_canonical_form EXPORT to_canonical_formConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT to_canonical_formConfig DESTINATION share/grapenlp/to_canonical_form/cmake COMPONENT libgrapenlpdev)
export(TARGETS to_canonical_form FILE to_canonical_formConfig.cmake)

# Test files
if (BUILD_TESTING)
    add_executable(to_canonical_form_test test/to_canonical_form_test.cpp)
    set_target_properties(to_canonical_form_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(to_canonical_form_test
            to_canonical_form
            token
            )
endif (BUILD_TESTING)
