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

#include <array>

#include <grapenlp/error.h>
#include <grapenlp/u_trie.h>
#include <grapenlp/u_array.h>
#include <grapenlp/tokenization.h>
#include <grapenlp/u_lexmask.h>
#include <grapenlp/ul_rtno.h>

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;
typedef token<ua_input_iterator> ua_token;
typedef ua_token::ref_list::const_iterator ua_token_iterator;
typedef lexmask<ua_input_iterator, unichar> ua_lexmask;
typedef u_case_sensitive_word_mask<ua_input_iterator> ua_case_sensitive_word_mask;
typedef u_case_insensitive_word_mask<ua_input_iterator, u_tolower> ua_case_insensitive_word_mask;
typedef u_word_meta_mask<ua_input_iterator> ua_word_meta_mask;
typedef u_digit_meta_mask<ua_input_iterator> ua_digit_meta_mask;
typedef typename u_trie_with_ptr_data<u_array>::type ua_trie;
typedef typename u_trie_with_ptr_data<ua_lexmask>::type ual_trie;
typedef ul_rtno<ua_input_iterator> ual_rtno;

pair<unichar *, size_t> read_unichars(u_array &input)
{
	FILE *f(u_fopen("../test.txt", U_READ));
	if (f == NULL)
		fatal_error("Unable to open file to read\n");
	size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
	size_t input_unichar_count = input_byte_count / 2;
	unichar* s(new unichar[input_unichar_count]);
	u_fread(s, input_unichar_count, f);
	u_fclose(f);
	return make_pair(s, input_unichar_count);
}

const std::array<unichar, 4> beau = { {'b', 'e', 'a', 'u'} };
const std::array<unichar, 4> BeAu = { {'B', 'e', 'A', 'u'} };
const std::array<unichar, 4> digit_meta = { {'<', 'N', 'B', '>'} };
const std::array<unichar, 5> word_meta = { {'<', 'M', 'O', 'T', '>'} };
const std::array<unichar, 3> epsilon_meta = { {'<', 'E', '>'} };

const std::array<unichar, 5> ci_beau = { {'%', 'b', 'e', 'a', 'u'} };
const std::array<unichar, 5> cs_BeAu = { {'@', 'B', 'e', 'A', 'u'} };
const std::array<unichar, 5> ci_digit_meta = { {'%', '<', 'N', 'B', '>'} };
const std::array<unichar, 6> ci_word_meta = { {'%', '<', 'M', 'O', 'T', '>'} };

int main(int argc, unichar **argv)
{
	u_array input(read_unichars(input));

	ua_token::ref_list the_token_list;
	tokenize<u_array::const_iterator>(input.begin(), input.end(), the_token_list);

#ifdef TRACE
	ual_rtno grammar('q');
#else
	ual_rtno grammar;
#endif
	ual_trie ualt;
	ua_trie uat;

	/*
	 * Output arrays
	 */

	u_printf("Output arrays\n");

	u_array *a_beau = new u_array(beau);
	ua_trie::string &uas_beau = uat.epsilon().concat(a_beau->begin(), a_beau->end());
	uas_beau.data = a_beau;
	u_printf("%c %d %c %d %c %d %c %d\n", uas_beau.prefix().prefix().prefix().back(), uas_beau.prefix().prefix().prefix().size(), uas_beau.prefix().prefix().back(), uas_beau.prefix().prefix().size(), uas_beau.prefix().back(), uas_beau.prefix().size(), uas_beau.back(), uas_beau.size());

	u_array *a_BeAu = new u_array(BeAu);
	ua_trie::string &uas_BeAu = uat.epsilon().concat(a_BeAu->begin(), a_BeAu->end());
	uas_BeAu.data = a_BeAu;
	u_printf("%c %d %c %d %c %d %c %d\n", uas_BeAu.prefix().prefix().prefix().back(), uas_BeAu.prefix().prefix().prefix().size(), uas_BeAu.prefix().prefix().back(), uas_BeAu.prefix().prefix().size(), uas_BeAu.prefix().back(), uas_BeAu.prefix().size(), uas_BeAu.back(), uas_BeAu.size());

	u_array *a_word_meta = new u_array(word_meta);
	ua_trie::string &uas_word_meta = uat.epsilon().concat(a_word_meta->begin(), a_word_meta->end());
	uas_word_meta.data = a_word_meta;
	u_printf("%c %d %c %d %c %d %c %d %c %d\n", uas_word_meta.prefix().prefix().prefix().prefix().back(), uas_word_meta.prefix().prefix().prefix().prefix().size(), uas_word_meta.prefix().prefix().prefix().back(), uas_word_meta.prefix().prefix().prefix().size(), uas_word_meta.prefix().prefix().back(), uas_word_meta.prefix().prefix().size(), uas_word_meta.prefix().back(), uas_word_meta.prefix().size(), uas_word_meta.back(), uas_word_meta.size());

	u_array *a_digit_meta = new u_array(digit_meta);
	ua_trie::string &uas_digit_meta = uat.epsilon().concat(a_digit_meta->begin(), a_digit_meta->end());
	uas_digit_meta.data = a_digit_meta;
	u_printf("%c %d %c %d %c %d %c %d\n", uas_digit_meta.prefix().prefix().prefix().back(), uas_digit_meta.prefix().prefix().prefix().size(), uas_digit_meta.prefix().prefix().back(), uas_digit_meta.prefix().prefix().size(), uas_digit_meta.prefix().back(), uas_digit_meta.prefix().size(), uas_digit_meta.back(), uas_digit_meta.size());

	u_array *a_epsilon_meta = new u_array(epsilon_meta);
	ua_trie::string &uas_epsilon_meta = uat.epsilon().concat(a_epsilon_meta->begin(), a_epsilon_meta->end());
	uas_epsilon_meta.data = a_epsilon_meta;
	u_printf("%c %d %c %d %c %d\n", uas_epsilon_meta.prefix().prefix().back(), uas_epsilon_meta.prefix().prefix().size(), uas_epsilon_meta.prefix().back(), uas_epsilon_meta.prefix().size(), uas_epsilon_meta.back(), uas_epsilon_meta.size());

	/*
	 * Lexical masks
	 */

	u_printf("Lexical masks\n");

	ual_trie::string &uals_ci_beau = ualt.epsilon().concat(ci_beau.begin(), ci_beau.end());
	ua_case_insensitive_word_mask *l_ci_beau = new ua_case_insensitive_word_mask(*uas_beau.data);
	uals_ci_beau.data = l_ci_beau;
	u_printf("%c %d %c %d %c %d %c %d %c %d\n", uals_ci_beau.prefix().prefix().prefix().prefix().back(), uals_ci_beau.prefix().prefix().prefix().prefix().size(), uals_ci_beau.prefix().prefix().prefix().back(), uals_ci_beau.prefix().prefix().prefix().size(), uals_ci_beau.prefix().prefix().back(), uals_ci_beau.prefix().prefix().size(), uals_ci_beau.prefix().back(), uals_ci_beau.prefix().size(), uals_ci_beau.back(), uals_ci_beau.size());

	ual_trie::string &uals_cs_BeAu = ualt.epsilon().concat(cs_BeAu.begin(), cs_BeAu.end());
	ua_case_sensitive_word_mask *l_cs_BeAu = new ua_case_sensitive_word_mask(*uas_BeAu.data);
	uals_cs_BeAu.data = l_cs_BeAu;
	u_printf("%c %d %c %d %c %d %c %d %c %d\n", uals_cs_BeAu.prefix().prefix().prefix().prefix().back(), uals_cs_BeAu.prefix().prefix().prefix().prefix().size(), uals_cs_BeAu.prefix().prefix().prefix().back(), uals_cs_BeAu.prefix().prefix().prefix().size(), uals_cs_BeAu.prefix().prefix().back(), uals_cs_BeAu.prefix().prefix().size(), uals_cs_BeAu.prefix().back(), uals_cs_BeAu.prefix().size(), uals_cs_BeAu.back(), uals_cs_BeAu.size());

	ual_trie::string &uals_ci_word_meta = ualt.epsilon().concat(ci_word_meta.begin(), ci_word_meta.end());
	ua_word_meta_mask *l_ci_word_meta = new ua_word_meta_mask();
	uals_ci_word_meta.data = l_ci_word_meta;
	u_printf("%c %d %c %d %c %d %c %d %c %d %c %d\n", uals_ci_word_meta.prefix().prefix().prefix().prefix().prefix().back(), uals_ci_word_meta.prefix().prefix().prefix().prefix().prefix().size(), uals_ci_word_meta.prefix().prefix().prefix().prefix().back(), uals_ci_word_meta.prefix().prefix().prefix().prefix().size(), uals_ci_word_meta.prefix().prefix().prefix().back(), uals_ci_word_meta.prefix().prefix().prefix().size(), uals_ci_word_meta.prefix().prefix().back(), uals_ci_word_meta.prefix().prefix().size(), uals_ci_word_meta.prefix().back(), uals_ci_word_meta.prefix().size(), uals_ci_word_meta.back(), uals_ci_word_meta.size());

	ual_trie::string &uals_ci_digit_meta = ualt.epsilon().concat(ci_digit_meta.begin(), ci_digit_meta.end());
	ua_digit_meta_mask *l_ci_digit_meta = new ua_digit_meta_mask();
	uals_ci_digit_meta.data = l_ci_digit_meta;
	u_printf("%c %d %c %d %c %d %c %d %c %d\n", uals_ci_digit_meta.prefix().prefix().prefix().prefix().back(), uals_ci_digit_meta.prefix().prefix().prefix().prefix().size(), uals_ci_digit_meta.prefix().prefix().prefix().back(), uals_ci_digit_meta.prefix().prefix().prefix().size(), uals_ci_digit_meta.prefix().prefix().back(), uals_ci_digit_meta.prefix().prefix().size(), uals_ci_digit_meta.prefix().back(), uals_ci_digit_meta.prefix().size(), uals_ci_digit_meta.back(), uals_ci_digit_meta.size());

	/*
	 * RTNO
	 */

	u_printf("Create states\n");
	ual_rtno::state::ref s0 = grammar.create_state(true, false);
	ual_rtno::state::ref s1 = grammar.create_state(false, true);

	u_printf("Add epsilon transition\n");
	s0->add_epsilon_transition(*a_epsilon_meta, s1);
	u_printf("Add beau transition\n");
	s0->add_deleting_transition(l_ci_beau, *a_beau, s1);
	u_printf("Add BeAu transition\n");
	s0->add_deleting_transition(l_cs_BeAu, *a_BeAu, s1);
	u_printf("Add word_meta transition\n");
	s0->add_deleting_transition(l_ci_word_meta, *a_word_meta, s1);
	u_printf("Add digit_meta transition\n");
	s0->add_deleting_transition(l_ci_digit_meta, *a_digit_meta, s1);

	return 0;
}
