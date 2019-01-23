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

#include <grapenlp/mtrace.h>
#include <locale>
#include <iostream>
#include <fstream>

#include <grapenlp/luxw_rtno.h>
#include <grapenlp/tokenization.h>
#include <grapenlp/trie.h>
#include <grapenlp/ulxw_fst2_reader.h>
#include <grapenlp/compressed_delaf_reader.h>
#include <grapenlp/lw_rtno_weight_tagger.h>
#include <grapenlp/rtno_to_dot_serializer.h>

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;
typedef token<ua_input_iterator> ua_token;
typedef ua_token::ref_list::const_iterator ua_token_iterator;
typedef l_trie<unichar, ua_input_iterator> ual_trie;
typedef luxw_rtno<ua_input_iterator, int>::type ualuxiw_rtno;
typedef ulxw_fst2_reader<ua_input_iterator, std::plus<int> > ualxiw_fst2_reader;

void u_read_compressed_dico(compressed_delaf &dico)
{
	FILE *bin_delaf_file(fopen("../Data/Unitex/Spanish/Dela/delaf_mini.bin", U_READ));
	if (!bin_delaf_file)
		fatal_error("Unable to open bin delaf file\n");
	FILE *inf_delaf_file(u_fopen("../Data/Unitex/Spanish/Dela/delaf_mini.inf", U_READ));
	if (!inf_delaf_file)
		fatal_error("Unable to open inf delaf file\n");
	u_read(bin_delaf_file, inf_delaf_file, dico);
	fclose(bin_delaf_file);
	fclose(inf_delaf_file);
}

void u_read_grammar(ualuxiw_rtno &grammar, ual_trie &ualt, u_out_bound::trie &uobt, compressed_delaf &dico)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Graphs/dico_test.fst2", U_READ));
	if (f == NULL)
		fatal_error("Unable to open grammar file to read\n");
	ualxiw_fst2_reader()(f, grammar, ualt, uobt, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
#ifndef MTRACE
	setlocale(LC_CTYPE,"");
#endif
#ifdef TRACE
	ualuxiw_rtno grammar('q');
#else
	ualuxiw_rtno grammar;
#endif
	ual_trie ualt;
	u_out_bound::trie uobt;
	compressed_delaf dico;

	std::wcout << "Reading dico" << std::endl;
	u_read_compressed_dico(dico);
	std::wcout << "Reading grammar" << std::endl;
	u_read_grammar(grammar, ualt, uobt, dico);
	std::wcout << "Setting default weights" << std::endl;
	lw_rtno_weight_tag<ua_input_iterator, ualuxiw_rtno::tag_output>(grammar);
	std::wcout << "Converting grammar to dot" << std::endl;

	wofstream fout("../grammar.dot");
	if (fout)
		rtno_to_dot_serialize(fout, "axioma", grammar);
	else wcerr << L"Unable to open file \"grammar.dot\" for writing" << std::endl;
	return 0;
}
