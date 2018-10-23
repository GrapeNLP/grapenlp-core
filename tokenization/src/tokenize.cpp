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

#include <grapenlp/error.h>
#include <grapenlp/u_array.h>
#include <grapenlp/tokenization.h>

using namespace std;
using namespace grapenlp;

typedef u_array::const_iterator ua_input_iterator;
typedef token<ua_input_iterator> ua_token;

pair<unichar *, size_t> read_unichars()
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

void write_tokens(const ua_token::ref_list &the_token_list)
{
	FILE *f(u_fopen("../token.txt", U_WRITE));
	if (f == NULL)
		fatal_error("Unable to open file to write\n");
	ua_token::ref_list::const_iterator i(the_token_list.begin());
	ua_input_iterator j;
	for (; i != the_token_list.end(); ++i)
	{
		switch ((*i)->my_type)
		{
			case WORD_TOKEN: u_fprintf(f, "WORD: "); break;
			case UPPER_WORD_TOKEN: u_fprintf(f, "UPPER_WORD: "); break;
			case LOWER_WORD_TOKEN: u_fprintf(f, "LOWER_WORD: "); break;
			case FIRST_UPPER_WORD_TOKEN: u_fprintf(f, "FIRST_UPPER_WORD: "); break;
			case WHITE_TOKEN: u_fprintf(f, "WHITE: "); break;
			case DIGIT_TOKEN: u_fprintf(f, "DIGIT: "); break;
			case SYMBOL_TOKEN: u_fprintf(f, "SYMBOL: ");
		}
		for (j = (*i)->begin; j != (*i)->end; ++j)
			u_fprintf(f, "%c", *j);
		u_fprintf(f, "\n");
	}
	u_fclose(f);
}

int main(int argc, char **argv)
{
	u_array input(read_unichars());

	ua_token::ref_list the_token_list;
	tokenize<ua_input_iterator>(input.begin(), input.end(), the_token_list);

	write_tokens(the_token_list);

	return 0;
}
