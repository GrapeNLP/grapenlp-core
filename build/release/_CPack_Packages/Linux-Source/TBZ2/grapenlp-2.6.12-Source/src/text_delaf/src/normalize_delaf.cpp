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

#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/u_text_delaf_writer.h>

using namespace grapenlp;

void u_read_dico(const char *dico_path, tolower_u_text_delaf &dico)
{
	FILE *f(u_fopen(dico_path, U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read(f, dico);
	u_fclose(f);
}

void u_write_dico(const char *dico_path, tolower_u_text_delaf &dico)
{
	FILE *f(u_fopen(dico_path, U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file dico.txt for writing\n");
	u_write(f, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::wcout << L"Mandatory arguments:" << std::endl;
		std::wcout << L"1) Input DELAF .dic dictionary" << std::endl;
		std::wcout << L"2) Output DELAF .dic dictionary" << std::endl;
		exit(1);
	}

	tolower_u_text_delaf dico;
	std::wcout << L"Reading dico" << std::endl;
	u_read_dico(argv[1], dico);
	std::wcout << L"Writing dico" << std::endl;
	u_write_dico(argv[2], dico);
}
