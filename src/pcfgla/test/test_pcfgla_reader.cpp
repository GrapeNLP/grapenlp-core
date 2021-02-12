/*
 * GRAPENLP
 *
 * Copyright (C) 2011-2012 Universidad de Alicante <javier.sastre@gmail.com>
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

#include <grapenlp/pcfgla_reader.h>

using namespace grapenlp;
using namespace std;

typedef long double probability;
typedef unsigned int idx_type;

//const char* pcfgla_name= "mini16";
//const char* pcfgla_name= "test16";
const char* pcfgla_name= "mini/test16";
//const char* pcfgla_name= "eng_sm616";

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
	def_pcfgla_n_term_trie<idx_type>::type n_term_dico;
	def_pcfgla_lexicon_trie lexicon_dico;
	pcfgla<probability, idx_type> grammar(n_term_dico, lexicon_dico);
	pcfgla_reader<probability, idx_type>()(pcfgla_grammar_file, pcfgla_lexicon_file, grammar);
	u_fclose(pcfgla_grammar_file);
	u_fclose(pcfgla_lexicon_file);
	grammar.serialize(wcout);
	return 0;
}
