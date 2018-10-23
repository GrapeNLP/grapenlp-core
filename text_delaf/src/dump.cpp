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

#include <grapenlp/mtrace.h>
#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/u_text_delaf_writer.h>

using namespace grapenlp;

typedef u_text_delaf<u_identity> uid_text_delaf;

void u_read_dico(uid_text_delaf &dico)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Dela/delaf.dic", U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read(f, dico);
	u_fclose(f);
}

void u_write_dico(uid_text_delaf &dico)
{
	FILE *f(u_fopen("../dico.txt", U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file dico.txt for writing\n");
	u_write(f, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
#ifndef MTRACE
	setlocale(LC_CTYPE,"");
#endif
	uid_text_delaf dico;
	std::wcout << L"Reading dico" << std::endl;
	u_read_dico(dico);
	std::wcout << L"Writing dico" << std::endl;
	u_write_dico(dico);
	return 0;
}
