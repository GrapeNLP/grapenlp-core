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

#include <grapenlp/error.h>
#include <grapenlp/u_array.h>
#include <grapenlp/compressed_delaf_reader.h>
#include <grapenlp/compressed_delaf_entry_filter.h>
#include <grapenlp/tokenization.h>
#include <grapenlp/to_decompressed_canonical_form.h>

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;
typedef token<ua_input_iterator> ua_token;
typedef normalizer_iterator<u_tolower, ua_input_iterator> nua_input_iterator;

const std::array<unichar, 18> mark = { {'t', 'o', '_', 'c', 'a', 'n', 'o', 'n', 'i', 'c', 'a', 'l', '_', 'f', 'o', 'r', 'm', ' '} };

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

int main(int argc, char **argv)
{
	//Load input
	u_array input(u_fread("../test.txt"));

	ua_token::ref_list the_token_list;
	tokenize<ua_input_iterator>(input.begin(), input.end(), the_token_list);

	compressed_delaf dico;
	std::wcout << L"Reading dico" << std::endl;
	u_read_compressed_dico(dico);

	compressed_delaf::ust_string::const_ref v_pos_ref(dico.ppooss.get('V'));
	if (!v_pos_ref)
		fatal_error("'V' POS (Verb part-of-speech) not found in DELAF\n");
	unique_ptr<compressed_delaf_entry_filter<nua_input_iterator> > v_pos_filter_ref(new mandatory_pos_compressed_delaf_entry_filter<nua_input_iterator>(*v_pos_ref));

	//Get translation result
//	std::unique_ptr<u_array> result(to_decompressed_canonical_form<unichar, ua_input_iterator, ua_token::ref_list::const_iterator, u_tolower>(input.begin(), input.end(), the_token_list.begin(), the_token_list.end(), dico, *v_pos_filter_ref));
	u_array result;
	to_decompressed_canonical_form<unichar, ua_input_iterator, ua_token::ref_list::const_iterator, u_tolower, std::array<unichar, 18>::const_iterator>(input.begin(), input.end(), the_token_list.begin(), the_token_list.end(), dico, *v_pos_filter_ref, mark.begin(), mark.end(), result);

	//Write translation result
	FILE *f(u_fopen("../result.txt", U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file result.txt for writing\n");
	u_fwrite(result.begin(), result.size(), f);
	u_fclose(f);
	return 0;
}
