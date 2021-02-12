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

#ifndef GRAPENLP_TW_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_TW_FST2_TAG_OUTPUT_READER_H

#include <grapenlp/weight_transformer_traits.h>
#include <grapenlp/u_trie_string_const_ref_x_weight.h>
#include <grapenlp/t_fst2_tag_output_reader.h>
#include <grapenlp/w_fst2_tag_output_reader.h>

namespace grapenlp
{
	struct t_before_w_stop_char_evaluator
	{
		bool operator() (unichar c) const
		{ return c == U_ENDL || c == '+' || c == '-'; }
	};

	template<typename WeightTransformer>
	struct tw_fst2_tag_output_reader
	{
		typedef WeightTransformer weight_transformer;
		typedef typename weight_transformer::result_type weight;
		typedef weight_transformer_traits<WeightTransformer> the_weight_transformer_traits;
		typedef typename u_trie_string_const_ref_x_weight<weight>::type tag;

		typedef t_fst2_tag_output_reader<t_before_w_stop_char_evaluator> my_t_fst2_tag_output_reader;
		typedef w_fst2_tag_output_reader<weight> my_w_fst2_tag_output_reader;

		u_trie &ut;

		tw_fst2_tag_output_reader(u_trie &ut_): ut(ut_)
		{}

		//Retrieve output (trie string and weight, if present)
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			tag uts_cref_x_w(the_weight_transformer_traits::identity());
			if (c != '-' && c != '+')
			{
				t_before_w_stop_char_evaluator is_t_stop_char;
				my_t_fst2_tag_output_reader t_tor(is_t_stop_char, ut);
				uts_cref_x_w.ts_cref = t_tor(f, c, line_count);
			}
			if (c == '-' || c == '+')
			{
				my_w_fst2_tag_output_reader w_tor;
				uts_cref_x_w.w = w_tor(f, c, line_count);
			}
			return uts_cref_x_w;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_TW_FST2_TAG_OUTPUT_READER*/
