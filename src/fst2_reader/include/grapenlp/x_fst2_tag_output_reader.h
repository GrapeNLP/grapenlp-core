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

#ifndef GRAPENLP_X_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_X_FST2_TAG_OUTPUT_READER_H

#include <grapenlp/u_out_bound.h>

namespace grapenlp
{
	template<typename StopCharEvaluator>
	struct x_fst2_tag_output_reader
	{
		typedef u_out_bound_const_ref tag;

		StopCharEvaluator is_stop_char;
		u_out_bound_trie &uobt;

		x_fst2_tag_output_reader(StopCharEvaluator is_stop_char_, u_out_bound_trie &uobt_): is_stop_char(is_stop_char_), uobt(uobt_)
		{}

		//Retrieve output bound, if present
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			if (is_stop_char(c))
				fatal_error("In line %u of .fst2 file: explicit empty output\n", line_count);
			if (c != '<')
				fatal_error("In line %u of .fst2 file: first output tag char should be '<' but got %c\n", line_count, c);
			//Suppose output bound is a left bound
			bool left(true);
			bool right(false);
			typename u_out_bound::trie::string::ref uobts = &uobt.epsilon();

			if (is_stop_char(c = (unichar)u_fgetc(f)))
				fatal_error("In line %u of .fst2 file: unterminated output bound\n", line_count);
			if (c == '>')
				fatal_error("In line %u of .fst2 file: anonymous output bound\n", line_count);
			//This is not a left bound but a right bound
			if (c == '/')
			{
				left = false;
				right = true;
				if (is_stop_char(c = (unichar)u_fgetc(f)))
					fatal_error("In line %u of .fst2 file: unterminated right closing output bound\n", line_count);
				if (c == '>')
					fatal_error("In line %u of .fst2 file: anonymous output bound\n", line_count);
			}
			do
			{
				uobts = &(*uobts + c);
#ifdef TRACE
				std::wcout << c;
#endif
			} while (!is_stop_char(c = (unichar)u_fgetc(f)) && c != '/' && c != '>');
			if (is_stop_char(c))
				fatal_error("In line %u of .fst2 file: unterminated output bound\n", line_count);
			//This is not a left bound but an empty bound
			if (c == '/')
			{
				if (right)
					fatal_error("In line %u of .fst2 file: right output bound also declared as empty output bound\n", line_count);
				left = true;
				right = true;
				c = (unichar)u_fgetc(f);
			}
			if (c != '>')
				fatal_error("In line %u of .fst2 file: output bound missing right delimiter '>'\n", line_count);
			c = u_fgetc(f);
			//If the output bound is new, create it
			if (!uobts->data)
				uobts->data = new u_out_bound_const_ref_triplet();
			return uobts->data->get(uobts, left, right);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_X_FST2_TAG_OUTPUT_READER*/
