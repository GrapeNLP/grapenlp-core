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

#ifndef GRAPENLP_INT_W_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_INT_W_FST2_TAG_OUTPUT_READER_H

#ifdef TRACE
#include <iostream>
#endif

#include <grapenlp/unicode.h>

namespace grapenlp
{
	template<typename IntWeight>
	struct int_w_fst2_tag_output_reader
	{
		typedef IntWeight tag;

		int_w_fst2_tag_output_reader()
		{}

		//Retrieve output weight
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			tag w = 0;
			tag sign(1);
			if (c == '-')
			{
				sign = -1;
				c = u_fgetc(f);
#ifdef TRACE
				std::wcout << "-";
#endif
			}
			else if (c == '+')
			{
#ifdef TRACE
				std::wcout << "+";
#endif
				c = u_fgetc(f);
			}
			if (!u_is_digit(c))
				fatal_error("In line %u of .fst2 file: expecting a '+', '-' or digit but got '%c'\n", line_count, c);
			do
			{
#ifdef TRACE
				std::wcout << c;
#endif
				w = w * ((tag)10) + ((tag)c) - ((tag)'0');
				c = u_fgetc(f);
			}while (u_is_digit(c));
			w *= sign;
			return w;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_INT_W_FST2_TAG_OUTPUT_READER*/
