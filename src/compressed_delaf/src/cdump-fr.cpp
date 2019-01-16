/*
 * GRAPENLP
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

#include <grapenlp/compressed_delaf_reader.h>
#include <grapenlp/decompress_delaf_writer.h>

using namespace grapenlp;

void u_read_compressed_dico(compressed_delaf &dico)
{
	FILE *bin_delaf_file(fopen("/opt/Unitex/French/Dela/dela-fr-public.bin", U_READ));
	if (!bin_delaf_file)
		fatal_error("Unable to open bin delaf file\n");
	FILE *inf_delaf_file(u_fopen("/opt/Unitex/French/Dela/dela-fr-public.inf", U_READ));
	if (!inf_delaf_file)
		fatal_error("Unable to open inf delaf file\n");
	u_read(bin_delaf_file, inf_delaf_file, dico);
	fclose(bin_delaf_file);
	fclose(inf_delaf_file);
}

void u_write_dico(compressed_delaf &dico)
{
	FILE *f(u_fopen("../dico-fr.txt", U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file dico.txt for writing\n");
	u_decompress_delaf_write(f, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
	compressed_delaf dico;
	std::wcout << L"Reading dico" << std::endl;
	u_read_compressed_dico(dico);
	std::wcout << L"Writing dico" << std::endl;
	u_write_dico(dico);
}
