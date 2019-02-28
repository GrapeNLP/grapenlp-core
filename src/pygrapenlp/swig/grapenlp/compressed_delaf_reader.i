/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

/* compressed_delaf_reader.i */
%module compressed_delaf_reader
%include std_string.i
%include compressed_delaf.i
%{
#include <grapenlp/compressed_delaf_reader.h>
%}

namespace grapenlp
{
    %rename(u_read_compressed_delaf) u_read;
    void u_read(const std::string &bin_delaf_pathname, const std::string &inf_delaf_pathname, compressed_delaf &dico);
}
