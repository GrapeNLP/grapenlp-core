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

project(doc VERSION ${CHANGELOG_VERSION} LANGUAGES NONE)

#set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/doc)
set(DOXYFILE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(DOXYFILE_EXTRA_SOURCES "\"${CMAKE_SOURCE_DIR}/README.md\" \"${CMAKE_SOURCE_DIR}/CHANGES\" \"${CMAKE_SOURCE_DIR}/LICENSE\"")
set(DOXYFILE_LATEX OFF)
set(DOXYFILE_HTML_DIR html)
set(DOXYFILE_LATEX_DIR latex)
set(DOXYFILE_MAIN_MDFILE "${CMAKE_SOURCE_DIR}/README.md")
get_directory_property(DOXYFILE_PROJECT_NAME DIRECTORY "${DOXYFILE_SOURCE_DIR}" DEFINITION PROJECT_NAME)
get_directory_property(DOXYFILE_PROJECT_VERSION DIRECTORY "${DOXYFILE_SOURCE_DIR}" DEFINITION PROJECT_VERSION)
get_directory_property(DOXYFILE_PROJECT_DESCRIPTION DIRECTORY "${DOXYFILE_SOURCE_DIR}" DEFINITION PROJECT_DESCRIPTION)
include(UseDoxygen)
if (DOXYGEN_FOUND)
    add_custom_target(doxygen_extra
            COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/html"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/index.html" "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/CHANGES" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/html"
            )
    add_dependencies(doxygen doxygen_extra)
    install(DIRECTORY "${CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY}/"
            DESTINATION "${CMAKE_INSTALL_DOCDIR}/libgrapenlp-doc"
            COMPONENT libgrapenlpdoc OPTIONAL)
endif (DOXYGEN_FOUND)