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

project(compressed_delaf VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_library(compressed_delaf STATIC
        src/bin_delaf.cpp
        src/inf_delaf.cpp
        src/bin_delaf_reader.cpp
        src/inf_delaf_reader.cpp
        src/compressed_delaf_reader.cpp
        src/decompress_delaf_writer.cpp
        src/compressed_delaf_entry_filter.cpp
        src/compressed_delaf_entry_filter_factory.cpp
        )
target_include_directories(compressed_delaf PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

install(TARGETS compressed_delaf EXPORT compressed_delafConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlpdev)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
install(EXPORT compressed_delafConfig DESTINATION share/grapenlp/compressed_delaf/cmake COMPONENT libgrapenlpdev)
export(TARGETS compressed_delaf FILE compressed_delafConfig.cmake)

target_link_libraries(compressed_delaf
        delaf
        )

add_executable(cdump src/cdump.cpp)
target_link_libraries(cdump compressed_delaf)

add_executable(filter_compressed_delaf src/filter_compressed_delaf.cpp)
target_link_libraries(filter_compressed_delaf compressed_delaf)

#Test files
add_executable(test_compressed_delaf test/test_compressed_delaf.cpp)
target_link_libraries(test_compressed_delaf compressed_delaf)
