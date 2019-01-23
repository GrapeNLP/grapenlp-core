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

using namespace grapenlp;

void u_read_dico(tolower_u_text_delaf &d)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Dela/delaf.dic", U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read<u_tolower>(f, d);
	u_fclose(f);
}

int main(int argc, char **argv)
{
	tolower_u_text_delaf d;
	std::wcout << L"Reading dico" << std::endl;
	u_read_dico(d);
	std::wcout << L"Writing ppooss" << std::endl;

	FILE *f(u_fopen("../ppooss.txt", U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file ppooss.txt for writing\n");

	u_set_trie::const_iterator i(d.ppooss.begin());
	++i;
	while (i != d.ppooss.end())
	{
		if (i->data)
		{
//			u_fprintf(f, "%d X ", i->data->size());
			u_write(f, static_cast<const u_trie::string&>(*i).begin(), static_cast<const u_trie::string&>(*i).end());
			u_fputc('\n', f);
		}
		++i;
	}
	u_fclose(f);
}
