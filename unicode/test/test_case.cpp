/*
 * GRAPE
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

#include <grape/error.h>
#include <grape/u_array.h>

using namespace grape;

std::pair<unichar *, std::size_t> read_unichars(u_array &input)
{
	FILE *f(u_fopen("../alpha.txt", U_READ));
	if (f == NULL)
		fatal_error("Unable to open text file to read\n");
	std::size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
	std::size_t input_unichar_count = input_byte_count / 2;
	unichar* s(new unichar[input_unichar_count]);
	u_fread(s, input_unichar_count, f);
	u_fclose(f);
	return std::make_pair(s, input_unichar_count);
}

int main(int argc, char **argv)
{
	u_array input(read_unichars(input));
	u_array lower(input, u_tolower());
	u_array upper(input, u_toupper());

	FILE *f(u_fopen("../case.txt", U_WRITE));

	std::size_t i;
	for (i = 0; i < input.size(); ++i)
	{
			if (u_is_lower(input[i]))
			{
				u_printf("lower ");
				u_fprintf(f, "lower ");
			}
			else if (u_is_upper(input[i]))
			{
				u_printf("upper ");
				u_fprintf(f, "upper ");
			}
			else
			{
				u_printf("xxxxx ");
				u_fprintf(f, "xxxxx ");
			}
			u_printf("ori = %c; lower = %c; upper = %c", input[i], lower[i], upper[i]);
			u_fprintf(f, "ori = %c; lower = %c; upper = %c\n", input[i], lower[i], upper[i]);
	}

	u_fclose(f);
//	u_array::const_iterator i;
//	u_tolower utl;
//	u_toupper utu;
//	for (i = input.begin(); i != input.end(); ++i)
//		u_printf("u_tolower(%c, %d) = %c %d\n", *i, *i, utl(*i), utl(*i));
//	for (i = input.begin(); i != input.end(); ++i)
//		u_printf("u_toupper(%c, %d) = %c %d\n", *i, *i, utu(*i), utu(*i));
	return 0;
}
