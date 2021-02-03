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

project(libgrapenlp VERSION ${CHANGELOG_VERSION} LANGUAGES CXX)

add_library(grapenlp SHARED
        src/ualxiw_manager.cpp
        )
target_include_directories(grapenlp PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(grapenlp
        manager
        )
set_target_properties (grapenlp PROPERTIES
        VERSION ${CHANGELOG_VERSION}
        )

install(TARGETS grapenlp EXPORT grapenlpConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libgrapenlp)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT libgrapenlpdev)
if (LSB_RELEASE_ID_SHORT STREQUAL "Ubuntu")
install(FILES "${CMAKE_BINARY_DIR}/debian/copyright"
        "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/libgrapenlp"
        COMPONENT libgrapenlp)
install(FILES "${CMAKE_BINARY_DIR}/debian/copyright"
        "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/libgrapenlp-dev"
        COMPONENT libgrapenlpdev)
endif (LSB_RELEASE_ID_SHORT STREQUAL "Ubuntu")
install(EXPORT grapenlpConfig DESTINATION share/grapenlp/grapenlp/cmake COMPONENT libgrapenlpdev)
export(TARGETS grapenlp FILE grapenlpConfig.cmake)
