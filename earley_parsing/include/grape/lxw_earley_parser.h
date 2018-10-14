/*
 * GRAPE
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

#ifndef GRAPE_LXW_EARLEY_PARSER_H
#define GRAPE_LXW_EARLEY_PARSER_H

#ifdef TRACE
#include <grape/iostream.h>
#endif

#include <grape/weight_transformer_traits.h>
#include <grape/earley_parser.h>
#include <grape/segment_map_x_weight.h>
#include <grape/lxw_rtno.h>

namespace grape
{
	template<typename InputIterator, typename SourceRef, typename Id, typename WeightTransformer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#ifdef TRACE
	struct lxw_earley_parser: public earley_parser<typename lxwns_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_input, typename lxwns_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_output, SourceRef, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, serializer<segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice> >, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, segment_map_x_weight_composer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef earley_parser<typename lxwns_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_input, typename lxwns_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_output, SourceRef, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, serializer<segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice> >, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, segment_map_x_weight_composer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#else
	struct lxw_earley_parser: public earley_parser<typename lxw_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_input, typename lxw_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_output, SourceRef, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, segment_map_x_weight_composer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef earley_parser<typename lxw_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_input, typename lxw_rtno<InputIterator, Id, typename WeightTransformer::result_type>::type::tag_output, SourceRef, segment_map_x_weight<SourceRef, Id, typename WeightTransformer::result_type, output_set_impl_choice>, segment_map_x_weight_transformer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, segment_map_x_weight_composer<SourceRef, Id, WeightTransformer, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::match match;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::composer composer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		typedef WeightTransformer weight_transformer;
		typedef weight_transformer_traits<weight_transformer> the_weight_transformer_traits;

		lxw_earley_parser(): base_type()
		{}
		lxw_earley_parser(match input_match_, transformer gamma_, composer circ_): base_type(input_match_, gamma_, circ_)
		{}

		blackboard_set& operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, blackboard_set &result)
		{
			base_type::gamma.set(input_begin, input_end);
			return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end, result, blackboard(the_weight_transformer_traits::identity()));
		}
	};

	//This is just for homogeneity
	template<typename InputIterator, typename SourceRef, typename Id, typename WeightTransformer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lxw_earley_parser_impl_selector
	{ typedef lxw_earley_parser<InputIterator, SourceRef, Id, WeightTransformer, execution_state_set_impl_choice, output_set_impl_choice> type; };
} //namespace grape

#endif /*GRAPE_LXW_EARLEY_PARSER_H*/
