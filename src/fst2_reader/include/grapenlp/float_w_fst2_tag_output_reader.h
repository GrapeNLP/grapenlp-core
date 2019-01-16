/*
 * GRAPENLP
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

#ifndef GRAPENLP_FLOAT_W_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_FLOAT_W_FST2_TAG_OUTPUT_READER_H

#ifdef TRACE
#include <iostream>
#endif

#include <grapenlp/unicode.h>

namespace grapenlp
{
	template<typename FloatWeight>
	struct float_w_fst2_tag_output_reader
	{
		typedef FloatWeight tag;

		float_w_fst2_tag_output_reader()
		{}

		//Retrieve output weight
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			std::string s;
			//Read sign
			if (c != '+' && c != '-' && c != '.' && !u_is_digit(c))
				fatal_error("In line %u of .fst2 file: expecting a '+', '-', '.' or digit but got '%c'\n", line_count, c);
			if (c == '-' || c == '+')
			{
				s += static_cast<char>(c);
				c = u_fgetc(f);
#ifdef TRACE
				std::wcout << c;
#endif
			}
			//Read mantissa's integer part
			if (c != '.' && !u_is_digit(c))
				fatal_error("In line %u of .fst2 file: expecting a '.' or digit but got '%c'\n", line_count, c);
			while (!feof(f) && u_is_digit(c))
			{
				s += static_cast<char>(c);
				c = u_fgetc(f);
#ifdef TRACE
				std::wcout << c;
#endif
			}
			//Read mantissa's decimal part
			if (!feof(f) && c == '.')
			{
				//Add dot
				s += static_cast<char>(c);
				c = u_fgetc(f);
				//Read decimal digits
				while (!feof(f) && u_is_digit(c))
				{
					s += static_cast<char>(c);
					c = u_fgetc(f);
				}
			}
			//Read exponent
			if (!feof(f) && (c == 'E' || c == 'e'))
			{
				s += static_cast<char>(c);
				c = u_fgetc(f);
				//Read sign
				if (c != '+' && c != '-' && !u_is_digit(c))
					fatal_error("In line %u of .fst2 file: expecting a '+', '-' or digit but got '%c'\n", line_count, c);
				if (c == '-' || c == '+')
				{
					s += static_cast<char>(c);
					c = u_fgetc(f);
				}
				//Read digits
				if (!u_is_digit(c))
					fatal_error("In line %u of .fst2 file: expecting a '+', '-' or digit but got '%c'\n", line_count, c);
				do
				{
					s += static_cast<char>(c);
					c = u_fgetc(f);
				} while (!feof(f) && u_is_digit(c));
			}
			return boost::lexical_cast<tag>(s);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_FLOAT_W_FST2_TAG_OUTPUT_READER*/
