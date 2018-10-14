/*
 * GRAPE
 *
 * Copyright (C) 2004-2018 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

#ifndef GRAPE_COMPRESSED_DELAF_READER_H
#define GRAPE_COMPRESSED_DELAF_READER_H

#include <cstdio>

#include <grape/bin_delaf_reader.h>
#include <grape/inf_delaf_reader.h>
#include <grape/compressed_delaf.h>

namespace grape
{
	void u_read(FILE *bin_delaf_file, FILE *inf_delaf_file, compressed_delaf &dico)
	{
		u_read(bin_delaf_file, (bin_delaf&)dico);
		u_read(inf_delaf_file, (inf_delaf&)dico);
	}

	void u_read(const std::string &bin_delaf_pathname, const std::string &inf_delaf_pathname, compressed_delaf &dico)
	{
		FILE *bin_delaf_file(fopen(bin_delaf_pathname.c_str(), U_READ));
		if (!bin_delaf_file)
			fatal_error("Unable to open bin delaf file\n");
		FILE *inf_delaf_file(u_fopen(inf_delaf_pathname.c_str(), U_READ));
		if (!inf_delaf_file)
			fatal_error("Unable to open inf delaf file\n");
		u_read(bin_delaf_file, inf_delaf_file, dico);
		fclose(bin_delaf_file);
		fclose(inf_delaf_file);
	}
} //namespace grape

#endif /*GRAPE_COMPRESSED_DELAF_READER_H*/
