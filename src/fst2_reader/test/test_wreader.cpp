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

#include <iostream>
#include <fstream>
#include <locale>

#include <grapenlp/error.h>
#include <grapenlp/trie.h>
#include <grapenlp/tokenization.h>
#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/luaw_rtno.h>
#include <grapenlp/uluaw_fst2_reader.h>
#ifdef TRACE
#include <grapenlp/rtno_to_dot_serializer.h>
#endif

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;
typedef token<ua_input_iterator> ua_token;
typedef ua_token::ref_list::const_iterator ua_token_iterator;
typedef l_trie<unichar, ua_input_iterator> ual_trie;
typedef trie_with_ptr_data<unichar, u_array> ua_trie;
#ifdef TRACE
typedef luawns_rtno<ua_input_iterator, int>::type ualuaw_rtno;
#else
typedef luaw_rtno<ua_input_iterator, int>::type ualuaw_rtno;
#endif
typedef uluaw_fst2_reader<ua_input_iterator, std::plus<int> > ualuaw_fst2_reader;

void u_read_dico(tolower_u_text_delaf &dico)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Dela/delaf.dic", U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read<u_tolower>(f, dico);
	u_fclose(f);
}

void u_read_grammar(ualuaw_rtno &grammar, ual_trie &ualt, ua_trie &uat, tolower_u_text_delaf &dico)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Graphs/wdico_test.fst2", U_READ));
	if (f == NULL)
		fatal_error("Unable to open grammar file to read\n");
	ualuaw_fst2_reader()(f, grammar, ualt, uat, dico);
	u_fclose(f);
}

int main(int argc, char **argv)
{
	ualuaw_rtno grammar;
	ual_trie ualt;
	ua_trie uat;
	tolower_u_text_delaf dico;

	wcout << "Reading dico" << std::endl;
	u_read_dico(dico);
	wcout << "Reading grammar" << std::endl;
	u_read_grammar(grammar, ualt, uat, dico);

    wcout << "Number of states: " << grammar.state_count() << std::endl;
    wcout << "Number of transitions: " << grammar.transition_count() << std::endl;
#ifdef TRACE
	wcout << "Converting grammar to dot" << std::endl;
	const locale l(setlocale(LC_CTYPE,""));
	wofstream fout("../grammar.dot");
	fout.imbue(l);
	if (fout)
	{
		rtno_to_dot_serialize(fout, "axioma", L'q', grammar);
		fout.close();
	}
	else wcerr << L"Unable to open file \"grammar.dot\" for writing" << std::endl;
#endif
	return 0;
}
