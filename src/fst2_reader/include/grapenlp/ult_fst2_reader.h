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

#ifndef GRAPENLP_ULT_FST2_READER_H
#define GRAPENLP_ULT_FST2_READER_H

#include <array>

#include <grapenlp/lut_rtno.h>
#include <grapenlp/t_fst2_tag_output_reader.h>
#include <grapenlp/ul_fst2_reader.h>

namespace grapenlp
{
	struct t_stop_char_evaluator
	{
		bool operator() (unichar c) const
		{ return c == U_ENDL; }
	};

	template<typename InputIterator, typename CaseNormalizer=u_tolower>
	struct ult_fst2_reader: public ul_fst2_reader<InputIterator, t_fst2_tag_output_reader<t_stop_char_evaluator>, CaseNormalizer>
	{
		typedef t_fst2_tag_output_reader<t_stop_char_evaluator> my_t_fst2_tag_output_reader;
		typedef ul_fst2_reader<InputIterator, my_t_fst2_tag_output_reader, CaseNormalizer> base_type;
		typedef typename base_type::machine machine;

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, u_trie &ut, u_text_delaf<CaseNormalizer> &dico, u_context &ctx)
		{
			t_stop_char_evaluator is_stop_char;
			my_t_fst2_tag_output_reader tor(is_stop_char, ut);
			return base_type::operator() (f, grammar, ult, tor, dico, ctx);
		}

		int operator() (FILE *f, machine &grammar, ul_tag_input_trie<unichar, InputIterator> &ult, u_trie &ut, compressed_delaf &dico, u_context &ctx)
		{
			t_stop_char_evaluator is_stop_char;
			my_t_fst2_tag_output_reader tor(is_stop_char, ut);
			return base_type::operator() (f, grammar, ult, tor, dico, ctx);
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_ULT_FST2_READER*/
