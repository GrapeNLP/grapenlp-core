/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

#include <grapenlp/error.h>
#include <grapenlp/u_array.h>
#include <grapenlp/u_text_delaf_reader.h>
#include <grapenlp/u_text_delaf_entry_filter.h>
#include <grapenlp/tokenization.h>
#include <grapenlp/to_canonical_form.h>

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;
typedef token<ua_input_iterator> ua_token;
typedef text_delaf_entry_filter<unichar, u_tolower> ulc_text_delaf_entry_filter;

const std::array<unichar, 18> mark = { {'t', 'o', '_', 'c', 'a', 'n', 'o', 'n', 'i', 'c', 'a', 'l', '_', 'f', 'o', 'r', 'm', ' '} };

void u_read_dico(tolower_u_text_delaf &dico)
{
	FILE *f(u_fopen("../Data/Unitex/Spanish/Dela/delaf.dic", U_READ));
	if (f == NULL)
		fatal_error("Unable to open delaf file to read\n");
	u_read(f, dico);
	u_fclose(f);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	//Load input
	u_array input(u_fread("../test.txt"));

	ua_token::ref_list the_token_list;
	tokenize<ua_input_iterator>(input.begin(), input.end(), the_token_list);

	tolower_u_text_delaf dico;
	std::wcout << L"Reading dico" << std::endl;
	u_read_dico(dico);

	tolower_u_text_delaf::ust_string::const_ref v_pos_ref(dico.ppooss.get('V'));
	if (!v_pos_ref)
		fatal_error("'V' POS (Verb part-of-speech) not found in DELAF\n");
	unique_ptr<ulc_text_delaf_entry_filter> v_pos_filter_ref(new u_mandatory_pos_text_delaf_entry_filter<u_tolower>(*v_pos_ref));

	//Get translation result
//	std::unique_ptr<u_array> result(to_canonical_form<unichar, ua_input_iterator, ua_token::ref_list::const_iterator, u_tolower>(input.begin(), input.end(), the_token_list.begin(), the_token_list.end(), dico, *v_pos_filter_ref));
	u_array result;
	to_canonical_form<unichar, ua_input_iterator, ua_token::ref_list::const_iterator, u_tolower>(input.begin(), input.end(), the_token_list.begin(), the_token_list.end(), dico, *v_pos_filter_ref, mark.begin(), mark.end(), result);

	//Write translation result
	FILE *f(u_fopen("../result.txt", U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file result.txt for writing\n");
	u_fwrite(result.begin(), result.size(), f);
	u_fclose(f);
	return 0;
}
