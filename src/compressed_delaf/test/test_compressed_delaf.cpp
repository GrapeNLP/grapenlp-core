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

#include <array>

#include <grapenlp/unicode.h>
#include <grapenlp/error.h>
#include <grapenlp/compressed_delaf_reader.h>

using namespace std;
using namespace grapenlp;


template<typename Iterator>
void print_ambiguous_entry(const compressed_delaf &dico, Iterator word_begin, Iterator word_end)
{
	const inf_delaf::ambiguous_entry *ae(dico.get_word_properties(word_begin, word_end));
	if (ae)
		wcout << *ae << endl;
	else wcout << L"Palabra desconocida" << endl;
}

void u_read_compressed_dico(compressed_delaf &dico)
{
	FILE *bin_delaf_file(fopen("../Data/Unitex/Spanish/Dela/delaf_norm.bin", U_READ));
	if (!bin_delaf_file)
		fatal_error("Unable to open bin delaf file\n");
	FILE *inf_delaf_file(u_fopen("../Data/Unitex/Spanish/Dela/delaf_norm.inf", U_READ));
	if (!inf_delaf_file)
		fatal_error("Unable to open inf delaf file\n");
	u_read(bin_delaf_file, inf_delaf_file, dico);
	fclose(bin_delaf_file);
	fclose(inf_delaf_file);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
#ifndef MTRACE
	setlocale(LC_CTYPE,"");
#endif
	const std::array<unichar, 1> a = { {'a'} };
	const std::array<unichar, 3> ame = { {'a', 'm', 'e'} };
	const std::array<unichar, 6> qwerty = { {'q', 'w', 'e', 'r', 't', 'y'} };

	compressed_delaf dico;
	u_read_compressed_dico(dico);
	std::wcout << L"Loaded compressed DELAF" << std::endl;

	print_ambiguous_entry(dico, a.begin(), a.end());
	print_ambiguous_entry(dico, ame.begin(), ame.end());
	print_ambiguous_entry(dico, qwerty.begin(), qwerty.end());
	return 0;
}
