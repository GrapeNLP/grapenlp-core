/*
 * GRAPE
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

#ifndef GRAPE_T_FST2_TAG_OUTPUT_READER_H
#define GRAPE_T_FST2_TAG_OUTPUT_READER_H

#include <grape/u_trie.h>

namespace grape
{
	template<typename StopCharEvaluator>
	struct t_fst2_tag_output_reader
	{
		typedef u_trie_string_const_ref tag;

		StopCharEvaluator is_stop_char;
		u_trie &ut;

		t_fst2_tag_output_reader(StopCharEvaluator is_stop_char_, u_trie &ut_): is_stop_char(is_stop_char_), ut(ut_)
		{}

		//Retrieve output trie_string
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			if (is_stop_char(c))
				fatal_error("In line %u of .fst2 file: explicit empty output\n", line_count);
			u_trie_string_ref uts = &ut.epsilon();
			do
			{
				uts = &(*uts + c);
#ifdef TRACE
				std::wcout << c;
#endif
			} while (!is_stop_char(c = (unichar)u_fgetc(f)));
			//If the output bound is new, create it
			return uts;
		}
	};
} //namespace grape

#endif /*GRAPE_T_FST2_TAG_OUTPUT_READER*/
