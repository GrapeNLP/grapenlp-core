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

#ifndef GRAPENLP_LUAW_EARLEY_PARSER_H
#define GRAPENLP_LUAW_EARLEY_PARSER_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

#include <grapenlp/weight_transformer_traits.h>
#include <grapenlp/luaw_rtno.h>
#include <grapenlp/pool_sequence_x_weight.h>
#include <grapenlp/earley_parser.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename InputIterator, typename SourceRef, typename WeightTransformer, typename OutputUArrayPool, typename OutputUArraySerializer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct luaw_earley_parser: public earley_parser<
	        typename luawns_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_input,
	        typename luawns_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_output,
	        SourceRef,
	        pool_sequence_x_weight<OutputUArrayPool, typename WeightTransformer::result_type>,
	        pool_sequence_x_weight_serializer<OutputUArrayPool, typename WeightTransformer::result_type, OutputUArraySerializer>,
	        pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator<OutputUArrayPool, WeightTransformer>,
	        pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator2<OutputUArrayPool, WeightTransformer>,
	        execution_state_set_impl_choice,
	        output_set_impl_choice
	        >
	{
		typedef earley_parser<
                typename luawns_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_input,
                typename luawns_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_output,
                SourceRef,
                pool_sequence_x_weight<OutputUArrayPool, typename WeightTransformer::result_type>,
                pool_sequence_x_weight_serializer<OutputUArrayPool, typename WeightTransformer::result_type, OutputUArraySerializer>,
                pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator<OutputUArrayPool, WeightTransformer>,
                pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator2<OutputUArrayPool, WeightTransformer>,
                execution_state_set_impl_choice,
                output_set_impl_choice
		        > base_type;
#else
	template<typename InputIterator, typename SourceRef, typename WeightTransformer, typename OutputUArrayPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct luaw_earley_parser: public earley_parser<
	        typename luaw_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_input,
	        typename luaw_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_output,
	        SourceRef,
	        pool_sequence_x_weight<OutputUArrayPool,
	        typename WeightTransformer::result_type>,
	        pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator<OutputUArrayPool, WeightTransformer>,
	        pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator2<OutputUArrayPool, WeightTransformer>,
	        execution_state_set_impl_choice,
	        output_set_impl_choice
	        >
	{
		typedef earley_parser<
                typename luaw_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_input,
                typename luaw_rtno<InputIterator, typename WeightTransformer::result_type, u_context_mask>::tag_output,
                SourceRef,
                pool_sequence_x_weight<OutputUArrayPool,
                typename WeightTransformer::result_type>,
                pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator<OutputUArrayPool, WeightTransformer>,
                pool_sequence_x_weight_and_array_const_ref_x_weight_concatenator2<OutputUArrayPool, WeightTransformer>,
                execution_state_set_impl_choice,
                output_set_impl_choice
		        > base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
typedef typename base_type::match match;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		typedef WeightTransformer weight_transformer;
		typedef weight_transformer_traits<weight_transformer> the_weight_transformer_traits;

		luaw_earley_parser(): base_type()
		{}
		luaw_earley_parser(match input_match_, transformer gamma_): base_type(input_match_, gamma_)
		{}

		blackboard_set& operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const u_context &c, blackboard_set &result, const blackboard &empty_blackboard = blackboard(the_weight_transformer_traits::identity()))
		{ return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end, c, result, empty_blackboard); }
	};

	template<typename InputIterator, typename SourceRef, typename WeightTransformer, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct luaw_earley_parser_impl_selector
	{};

	template<typename InputIterator, typename SourceRef, typename WeightTransformer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct luaw_earley_parser_impl_selector<InputIterator, SourceRef, WeightTransformer, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>
	{
#ifdef TRACE
		typedef luaw_earley_parser<InputIterator, SourceRef, WeightTransformer, array_fake_pool<unichar>, serializer<array_fake_pool<unichar>::value_type>, execution_state_set_impl_choice, output_set_impl_choice> type;
#else
		typedef luaw_earley_parser<InputIterator, SourceRef, WeightTransformer, array_fake_pool<unichar>, execution_state_set_impl_choice, output_set_impl_choice> type;
#endif
	};

	template<typename InputIterator, typename SourceRef, typename WeightTransformer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct luaw_earley_parser_impl_selector<InputIterator, SourceRef, WeightTransformer, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>
	{
#ifdef TRACE
		typedef luaw_earley_parser<InputIterator, SourceRef, WeightTransformer, trie_string_ref_pool<unichar>, const_deref_serializer<typename trie_string_ref_pool<unichar>::base_type>, execution_state_set_impl_choice, output_set_impl_choice> type;
#else
		typedef luaw_earley_parser<InputIterator, SourceRef, WeightTransformer, trie_string_ref_pool<unichar>, execution_state_set_impl_choice, output_set_impl_choice> type;
#endif
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUAW_EARLEY_PARSER_H*/
