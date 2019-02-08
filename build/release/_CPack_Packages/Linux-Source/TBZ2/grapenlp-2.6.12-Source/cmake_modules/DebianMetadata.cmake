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

configure_file(${CMAKE_SOURCE_DIR}/LICENSE
        ${CMAKE_BINARY_DIR}/debian/copyright)
configure_file(${CMAKE_SOURCE_DIR}/CHANGES
        ${CMAKE_BINARY_DIR}/debian/changelog.Debian)
execute_process(COMMAND gzip -9 -c ${CMAKE_BINARY_DIR}/debian/changelog.Debian
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/debian
        OUTPUT_FILE "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz")