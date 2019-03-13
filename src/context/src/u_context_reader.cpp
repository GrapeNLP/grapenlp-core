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

#include <grapenlp/u_context_reader.h>

namespace grapenlp
{
	unichar u_read(FILE *f, u_context &ctx)
	{
		std::size_t max_line_size=10000;
		unsigned int line_count = 0;
		unichar line[max_line_size];
		unichar *key_begin;
		unichar *key_end;
		unichar *value_begin;
		unichar *value_end;
		unichar *aux;
		while (u_fgets(line, f) > 0)
		{
			++line_count;
			key_begin = line;
			//Skip whites before key
			while (u_is_white(*key_begin))
				++key_begin;
			//Skip empty line
			if (*key_begin == '\0')
				continue;
			if (!u_is_letter(*key_begin))
				fatal_error("In line %u of context file: key must start with letter\n", line_count);
			key_end = key_begin + 1;
			//Skip key characters
			while (!u_is_white(*key_end) && *key_end != '=' && *key_end != '\0')
			{
				if (!u_is_letter(*key_end) && !u_is_digit(*key_end) && *key_end != '_')
					fatal_error("In line %u of context file: illegal key character (only letters, digits and underscores allowed)\n", line_count);
				++key_end;
			}
			value_begin = key_end;
			//Skip whites after key
			while (u_is_white(*value_begin))
				++value_begin;
			if (*value_begin != '=')
				fatal_error("In line %u of context file: missing equal symbol after key\n", line_count);
			++value_begin;
			//Skip whites after key
			while (u_is_white(*value_begin))
				++value_begin;
			if (*value_begin == '\0')
				fatal_error("In line %u of context file: missing value after equal symbol\n", line_count);
			value_end = value_begin + 1;
			//Skip value characters
			while (!u_is_white(*value_end) && *value_end != '\0')
				++value_end;
			aux = value_end;
			//Skip whites after value
			while (u_is_white(*aux) && *aux != '\0')
				++aux;
			if (*aux != '\0')
				fatal_error("In line %u of context file: value is not to contain white spaces\n", line_count);
#ifdef TRACE
            for (aux = key_begin; aux < key_end; ++aux)
                std::wcout << *aux;
            std::wcout << L'=';
            for (aux = value_begin; aux < value_end; ++aux)
                std::wcout << *aux;
            std::wcout << std::endl;
#endif
			ctx.set(key_begin, key_end, value_begin, value_end);
		}
	}
} //namespace grapenlp
