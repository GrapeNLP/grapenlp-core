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

#ifndef GRAPENLP_XW_FST2_TAG_OUTPUT_READER_H
#define GRAPENLP_XW_FST2_TAG_OUTPUT_READER_H

#include <grapenlp/weight_transformer_traits.h>
#include <grapenlp/u_out_bound_const_ref_x_weight.h>
#include <grapenlp/x_fst2_tag_output_reader.h>
#include <grapenlp/w_fst2_tag_output_reader.h>

namespace grapenlp
{
	struct x_before_w_stop_char_evaluator
	{
		bool operator() (unichar c) const
		{ return c == U_ENDL; }
	};

	template<typename WeightTransformer>
	struct xw_fst2_tag_output_reader
	{
		typedef WeightTransformer weight_transformer;
		typedef typename weight_transformer::result_type weight;
		typedef weight_transformer_traits<WeightTransformer> the_weight_transformer_traits;
		typedef typename u_out_bound_const_ref_x_weight<weight>::type tag;

		typedef x_fst2_tag_output_reader<x_before_w_stop_char_evaluator> my_x_fst2_tag_output_reader;
		typedef w_fst2_tag_output_reader<weight> my_w_fst2_tag_output_reader;

		u_out_bound_trie &uobt;

		xw_fst2_tag_output_reader(u_out_bound_trie &uobt_): uobt(uobt_)
		{}

		//Retrieve output (bound and weight, if present)
		tag operator() (FILE *f, unichar &c, unsigned int &line_count) const
		{
			tag uob_cref_x_w(the_weight_transformer_traits::identity());
			if (c == '<')
			{
				x_before_w_stop_char_evaluator is_x_stop_char;
				my_x_fst2_tag_output_reader x_tor(is_x_stop_char, uobt);
				uob_cref_x_w.ob_cref = x_tor(f, c, line_count);
			}
			if (c == '-' || c == '+')
			{
				my_w_fst2_tag_output_reader w_tor;
				uob_cref_x_w.w = w_tor(f, c, line_count);
			}
			return uob_cref_x_w;
		}
	};
} //namespace grapenlp

#endif /*GRAPENLP_XW_FST2_TAG_OUTPUT_READER*/
