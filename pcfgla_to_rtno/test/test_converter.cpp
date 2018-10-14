/*
 * GRAPE
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@telefonica.net>
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

#ifdef MTRACE
#include <grape/mtrace.h>
#endif

#include <iostream>
#include <fstream>
#include <locale>

#include <grape/u_array.h>
#include <grape/pcfgla_reader.h>
#include <grape/compressed_delaf.h>
#include <grape/pcfgla_to_rtno.h>
#ifdef TRACE
#include <grape/rtno_to_dot_serializer.h>
#endif

using namespace grape;
using namespace std;

typedef u_array::const_iterator ua_input_iterator;
typedef long double probability;
typedef unsigned int idx_type;

//const char* pcfgla_name= "mini16";
//const char* pcfgla_name= "test16";
//const char* pcfgla_name= "mini/test16";
const char* pcfgla_name= "eng_sm616";

const char* base_path = "../Data/BerkeleyParser/en/";

int main(int argc, char **argv)
{
	std::string pcfgla_grammar_name(base_path);
	pcfgla_grammar_name += pcfgla_name;
	pcfgla_grammar_name += ".grammar";
	std::string pcfgla_lexicon_name(base_path);
	pcfgla_lexicon_name += pcfgla_name;
	pcfgla_lexicon_name += ".lexicon";

	FILE *pcfgla_grammar_file(u_fopen(pcfgla_grammar_name.c_str(), U_READ));
	if (!pcfgla_grammar_file)
		fatal_error("Unable to open BerkeleyParser grammar to read\n");
	FILE *pcfgla_lexicon_file(u_fopen(pcfgla_lexicon_name.c_str(), U_READ));
	if (!pcfgla_lexicon_file)
		fatal_error("Unable to open BerkeleyParser lexicon to read\n");
	wcout.precision(20);
	wcout.unsetf(ios_base::fixed);
//	wcout.setf(ios_base::scientific);
	def_pcfgla_to_rtno_n_term_trie<ua_input_iterator, probability, idx_type>::type n_term_dico;
	def_pcfgla_to_rtno_lexicon_trie<ua_input_iterator>::type lexicon_dico;
	pcfgla<probability, idx_type, def_pcfgla_to_rtno_n_term_trie_data<ua_input_iterator, probability, idx_type>, def_pcfgla_to_rtno_lexicon_trie_data<ua_input_iterator> > pcfgla_grammar(n_term_dico, lexicon_dico);
	pcfgla_reader<probability, idx_type, def_pcfgla_to_rtno_n_term_trie_data<ua_input_iterator, probability, idx_type>, def_pcfgla_to_rtno_lexicon_trie_data<ua_input_iterator> >()(pcfgla_grammar_file, pcfgla_lexicon_file, pcfgla_grammar);
	u_fclose(pcfgla_grammar_file);
	u_fclose(pcfgla_lexicon_file);
	lutwns_rtno<ua_input_iterator, probability>::type rtno_grammar;
	u_trie out_tag_trie;
	//Dummy compressed DELAF, just because the lexmask factory needs one but we will not define lexmasks referring to the dictionary
	compressed_delaf dico;
	pcfgla_to_rtno<ua_input_iterator, probability, idx_type>()(pcfgla_grammar, rtno_grammar, out_tag_trie, dico);
    std::wcout << "Number of states: " << rtno_grammar.state_count() << std::endl;
    std::wcout << "Number of transitions: " << rtno_grammar.transition_count() << std::endl;
#ifdef TRACE
	wcout << "Converting rtno grammar to dot" << std::endl;
	wofstream fout("../grammar.dot");

	fout.imbue(std::locale(setlocale(LC_CTYPE, NULL)));
	if (fout)
	{
		rtno_to_dot_serialize(fout, "axioma", L'q', rtno_grammar);
		fout.close();
	}
	else wcerr << L"Unable to open file \"grammar.dot\" for writing" << std::endl;
#endif
	return 0;
}
