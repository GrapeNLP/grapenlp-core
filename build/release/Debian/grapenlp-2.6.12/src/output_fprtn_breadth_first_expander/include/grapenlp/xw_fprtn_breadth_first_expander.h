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

#ifndef GRAPENLP_XW_FPRTN_BREADTH_FIRST_EXPANDER_H
#define GRAPENLP_XW_FPRTN_BREADTH_FIRST_EXPANDER_H

#include <grapenlp/weight_transformer_traits.h>
#include <grapenlp/segment_map_x_weight.h>
#include <grapenlp/xw_output_fprtn.h>
#include <grapenlp/fprtn_breadth_first_expander.h>

namespace grapenlp
{
	template<typename SourceRef, typename Id, typename WeightTransformer, typename RTNOTagInput, typename StateConstRefStackRefPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#ifdef TRACE
	struct xw_fprtn_breadth_first_expander: public fprtn_breadth_first_expander<SourceRef, typename xw_output_fprtn<SourceRef, Id, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, serializer<segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice> >, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, StateConstRefStackRefPool, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef fprtn_breadth_first_expander<SourceRef, typename xw_output_fprtn<SourceRef, Id, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, serializer<segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice> >, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, StateConstRefStackRefPool, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#else
	struct xw_fprtn_breadth_first_expander: public fprtn_breadth_first_expander<SourceRef, typename xw_output_fprtn<SourceRef, Id, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, StateConstRefStackRefPool, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef fprtn_breadth_first_expander<SourceRef, typename xw_output_fprtn<SourceRef, Id, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, StateConstRefStackRefPool, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::tag_input tag_input;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		typedef WeightTransformer weight_transformer;
		typedef weight_transformer_traits<weight_transformer> the_weight_transformer_traits;

		xw_fprtn_breadth_first_expander()
		{}

		blackboard_set& operator() (const machine& m, source_ref input_begin, source_ref input_end, blackboard_set &result)
		{
			base_type::gamma.set(input_begin, input_end);
			return base_type::operator()(m, result, blackboard(the_weight_transformer_traits::identity()));
		}
	};

	template<typename SourceRef, typename Id, typename WeightTransformer, typename RTNOTagInput, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct xw_fprtn_breadth_first_expander_impl_selector
	{};

	template<typename SourceRef, typename Id, typename WeightTransformer, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct xw_fprtn_breadth_first_expander_impl_selector<SourceRef, Id, WeightTransformer, RTNOTagInput, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef xw_fprtn_breadth_first_expander<SourceRef, Id, WeightTransformer, RTNOTagInput, array_fake_ref_pool<typename xw_output_fprtn<SourceRef, Id, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::type::state_const_ref>, execution_state_set_impl_choice, output_set_impl_choice> type;
	};

	template<typename SourceRef, typename Id, typename WeightTransformer, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct xw_fprtn_breadth_first_expander_impl_selector<SourceRef, Id, WeightTransformer, RTNOTagInput, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef xw_fprtn_breadth_first_expander<SourceRef, Id, WeightTransformer, RTNOTagInput, trie_string_ref_pool<typename xw_output_fprtn<SourceRef, Id, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::type::state_const_ref>, execution_state_set_impl_choice, output_set_impl_choice> type;
	};
}

#endif /*GRAPENLP_XW_FPRTN_BREADTH_FIRST_EXPANDER_H*/
