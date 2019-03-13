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

#ifndef GRAPENLP_AW_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H
#define GRAPENLP_AW_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

#include <grapenlp/aw_output_fprtn_top.h>
#include <grapenlp/pool_sequence_x_weight.h>
#include <grapenlp/wfprtn_top_blackboard_extractor.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename SourceRef, typename WeightTransformer, typename RTNOTagInput, typename OutputArrayPool, typename OutputArraySerializer, assoc_container_impl_choice execution_state_set_impl_choice>
	struct aw_fprtn_top_blackboard_extractor: public wfprtn_top_blackboard_extractor<SourceRef, typename aw_output_fprtn_top<u_context_mask, SourceRef, typename OutputArrayPool::char_type, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::tag_input, RTNOTagInput, pool_sequence_x_weight<OutputArrayPool, typename WeightTransformer::result_type>, pool_sequence_x_weight_serializer<OutputArrayPool, typename WeightTransformer::result_type, OutputArraySerializer>, pool_sequence_x_weight_and_array_const_ref_x_weight_unweighted_converse_concatenator<OutputArrayPool, typename WeightTransformer::result_type>, WeightTransformer, execution_state_set_impl_choice>
	{
		typedef wfprtn_top_blackboard_extractor<SourceRef, typename aw_output_fprtn_top<u_context_mask, SourceRef, typename OutputArrayPool::char_type, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::tag_input, RTNOTagInput, pool_sequence_x_weight<OutputArrayPool, typename WeightTransformer::result_type>, pool_sequence_x_weight_serializer<OutputArrayPool, typename WeightTransformer::result_type, OutputArraySerializer>, pool_sequence_x_weight_and_array_const_ref_x_weight_unweighted_converse_concatenator<OutputArrayPool, typename WeightTransformer::result_type>, WeightTransformer, execution_state_set_impl_choice> base_type;
#else
	template<typename SourceRef, typename WeightTransformer, typename RTNOTagInput, typename OutputArrayPool, assoc_container_impl_choice execution_state_set_impl_choice>
	struct aw_fprtn_top_blackboard_extractor: public wfprtn_top_blackboard_extractor<SourceRef, typename aw_output_fprtn_top<u_context_mask, SourceRef, typename OutputArrayPool::char_type, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::tag_input, RTNOTagInput, pool_sequence_x_weight<OutputArrayPool, typename WeightTransformer::result_type>, pool_sequence_x_weight_and_array_const_ref_x_weight_unweighted_converse_concatenator<OutputArrayPool, typename WeightTransformer::result_type>, WeightTransformer, execution_state_set_impl_choice>
	{
		typedef wfprtn_top_blackboard_extractor<SourceRef, typename aw_output_fprtn_top<u_context_mask, SourceRef, typename OutputArrayPool::char_type, typename WeightTransformer::result_type, RTNOTagInput, execution_state_set_impl_choice>::tag_input, RTNOTagInput, pool_sequence_x_weight<OutputArrayPool, typename WeightTransformer::result_type>, pool_sequence_x_weight_and_array_const_ref_x_weight_unweighted_converse_concatenator<OutputArrayPool, typename WeightTransformer::result_type>, WeightTransformer, execution_state_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::tag_input tag_input;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::unweighted_converse_transformer unweighted_converse_transformer;
		typedef typename base_type::weight_transformer weight_transformer;

		aw_fprtn_top_blackboard_extractor(): base_type()
		{}
		aw_fprtn_top_blackboard_extractor(unweighted_converse_transformer rgamma_): base_type(rgamma_)
		{}
	};

	template<typename SourceRef, typename OutputChart, typename WeightTransformer, typename RTNOTagInput, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
	struct aw_fprtn_top_blackboard_extractor_impl_selector
	{};

	template<typename SourceRef, typename OutputChar, typename WeightTransformer, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct aw_fprtn_top_blackboard_extractor_impl_selector<SourceRef, OutputChar, WeightTransformer, RTNOTagInput, ARRAYS, execution_state_set_impl_choice>
	{
#ifdef TRACE
		typedef aw_fprtn_top_blackboard_extractor<SourceRef, WeightTransformer, RTNOTagInput, array_fake_pool<OutputChar>, serializer<typename array_fake_pool<OutputChar>::value_type>, execution_state_set_impl_choice> type;
#else
		typedef aw_fprtn_top_blackboard_extractor<SourceRef, WeightTransformer, RTNOTagInput, array_fake_pool<OutputChar>, execution_state_set_impl_choice> type;
#endif
	};

	template<typename SourceRef, typename OutputChar, typename WeightTransformer, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct aw_fprtn_top_blackboard_extractor_impl_selector<SourceRef, OutputChar, WeightTransformer, RTNOTagInput, TRIE_STRINGS, execution_state_set_impl_choice>
	{
#ifdef TRACE
		typedef aw_fprtn_top_blackboard_extractor<SourceRef, WeightTransformer, RTNOTagInput, trie_string_ref_pool<OutputChar>, trie_string_deref_reverse_serializer<OutputChar>, execution_state_set_impl_choice> type;
#else
		typedef aw_fprtn_top_blackboard_extractor<SourceRef, WeightTransformer, RTNOTagInput, trie_string_ref_pool<OutputChar>, execution_state_set_impl_choice> type;
#endif
	};
}

#endif /*GRAPENLP_AW_WFPRTN_TOP_BLACKBOARD_EXTRACTOR_H*/
