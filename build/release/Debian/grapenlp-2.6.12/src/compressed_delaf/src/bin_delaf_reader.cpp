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

#include <grapenlp/bin_delaf_reader.h>
#include <grapenlp/file.h>

namespace grapenlp
{
	std::size_t u_read(FILE *f, bin_delaf &bin_dico)
	{
		std::size_t byte_count(fsize(f));
		std::unique_ptr<unsigned char> buffer(new unsigned char[byte_count]);
        //Getting here the result of fread in order to avoid warning, but doing nothing with it
		std::size_t read_byte_count(fread(buffer.get(), sizeof(unsigned char), byte_count, f));
		bin_dico.reset_buffer(buffer.release());
        return read_byte_count;
	}
} //namespace grapenlp

