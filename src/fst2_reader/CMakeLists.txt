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

project(fst2_reader VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(fst2_reader STATIC
        src/ul_tag_input.cpp
        src/ul_tag_input_factory.cpp
        src/ul_fst2_reader.cpp
        src/ulua_fst2_reader.cpp
        src/uluaw_fst2_reader.cpp
        src/ulw_fst2_reader.cpp
        src/ult_fst2_reader.cpp
        src/ultw_fst2_reader.cpp
        src/ulx_fst2_reader.cpp
        src/ulxw_fst2_reader.cpp
        src/ua_fst2_tag_output_reader.cpp
        src/uaw_fst2_tag_output_reader.cpp
        src/t_fst2_tag_output_reader.cpp
        src/x_fst2_tag_output_reader.cpp
        src/int_w_fst2_tag_output_reader.cpp
        src/float_w_fst2_tag_output_reader.cpp
        src/w_fst2_tag_output_reader.cpp
        src/tw_fst2_tag_output_reader.cpp
        src/xw_fst2_tag_output_reader.cpp
        )
target_include_directories(fst2_reader PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(fst2_reader
        machine
        rtno
        context_mask
        fst2_constants
        )

install(TARGETS fst2_reader EXPORT fst2_readerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/grapenlp COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT fst2_readerConfig DESTINATION share/grapenlp/fst2_reader/cmake COMPONENT libgrapenlpdev)
export(TARGETS fst2_reader FILE fst2_readerConfig.cmake)

#Test files
if (BUILD_TESTING)
    add_executable(test_reader test/test_reader.cpp)
    set_target_properties(test_reader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_reader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_wreader test/test_wreader.cpp)
    set_target_properties(test_wreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_wreader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_creader test/test_creader.cpp)
    set_target_properties(test_creader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_creader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_cwreader test/test_cwreader.cpp)
    set_target_properties(test_cwreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_cwreader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_treader test/test_treader.cpp)
    set_target_properties(test_treader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_treader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_ctreader test/test_ctreader.cpp)
    set_target_properties(test_ctreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_ctreader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_twreader test/test_twreader.cpp)
    set_target_properties(test_twreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_twreader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_ctwreader test/test_ctwreader.cpp)
    set_target_properties(test_ctwreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_ctwreader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_xreader test/test_xreader.cpp)
    set_target_properties(test_xreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_xreader
            fst2_reader
            rtno_to_dot_serializer
            )

    add_executable(test_cxreader test/test_cxreader.cpp)
    set_target_properties(test_cxreader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_RUNTIME_OUTPUT_DIRECTORY})
    target_link_libraries(test_cxreader
            fst2_reader
            rtno_to_dot_serializer
            )
endif (BUILD_TESTING)
