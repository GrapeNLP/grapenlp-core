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

project(cgrapenlp VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_executable(cgrapenlp src/grapenlp.cpp)
SET_TARGET_PROPERTIES(cgrapenlp PROPERTIES OUTPUT_NAME grapenlp)
target_link_libraries(cgrapenlp
        config
        grapenlp
        ${Boost_PROGRAM_OPTIONS_LIBRARY})

install(TARGETS cgrapenlp EXPORT cgrapenlpConfig
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT cgrapenlp)
if (LSB_RELEASE_ID_SHORT STREQUAL "Ubuntu")
install(FILES "${CMAKE_BINARY_DIR}/debian/copyright"
        "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/grapenlp"
        COMPONENT cgrapenlp)
endif (LSB_RELEASE_ID_SHORT STREQUAL "Ubuntu")
install(EXPORT cgrapenlpConfig DESTINATION share/grapenlp/grapenlp/cmake COMPONENT libgrapenlpdev)
export(TARGETS cgrapenlp FILE cgrapenlpConfig.cmake)
