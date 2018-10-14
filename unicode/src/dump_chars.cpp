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

#include <grape/unicode.h>

#define MAX_LETTERS 0x10000

using namespace grape;

int main(int argc, char **argv)
{
	std::size_t c;
	u_printf("%d %d", uppercase_table.size(), lowercase_table.size());
	FILE *upper_f(u_fopen("../uppercase.txt", U_WRITE));
	FILE *lower_f(u_fopen("../lowercase.txt", U_WRITE));
	FILE *nocase_f(u_fopen("../nocase.txt", U_WRITE));
	FILE *chars_f(u_fopen("../chars.txt", U_WRITE));
/*	if (uppercase_table[c])
	{
		u_fprintf(upper_f, "%c %d\n", c, c);
		u_fprintf(chars_f, "U %c %d\n", c, c);
	}
	if (lowercase_table[c])
	{
		u_fprintf(lower_f, "%c %d\n", c, c);
		u_fprintf(chars_f, "L %c %d\n", c, c);
	}
	if (!uppercase_table[c] && !lowercase_table[c])
	{
		u_fprintf(nocase_f, "%c %d\n", c, c);
		u_fprintf(chars_f, "X %c %d\n", c, c);
	}
	++c;*/
	for (c = 32; c != MAX_LETTERS; ++c)
	{
		if (uppercase_table.test(c))
		{
			u_fprintf(upper_f, "%c %d\n", c, c);
			u_fprintf(chars_f, "U %c %d\n", c, c);
		}
		if (lowercase_table.test(c))
		{
			u_fprintf(lower_f, "%c %d\n", c, c);
			u_fprintf(chars_f, "L %c %d\n", c, c);
		}
		if (!uppercase_table.test(c) && !lowercase_table.test(c))
		{
			u_fprintf(nocase_f, "%c %d\n", c, c);
			u_fprintf(chars_f, "X %c %d\n", c, c);
		}
	}
	u_fclose(upper_f);
	u_fclose(lower_f);
	u_fclose(nocase_f);
	u_fclose(chars_f);
	return 0;
}
