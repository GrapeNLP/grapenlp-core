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

#ifndef GRAPENLP_LX_EARLEY_PARSER_H
#define GRAPENLP_LX_EARLEY_PARSER_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

#include <grapenlp/earley_parser.h>
#include <grapenlp/segment.h>
#include <grapenlp/lx_rtno.h>

namespace grapenlp
{
	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, typename Id, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#ifdef TRACE
	struct lx_earley_parser: public earley_parser<typename lxns_rtno<InputIterator, Id, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::tag_input, typename lxns_rtno<InputIterator, Id, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::tag_output, SourceRef, ContextKey, ContextValue, segment_map<SourceRef, Id, output_set_impl_choice>, serializer<segment_map<SourceRef, Id, output_set_impl_choice> >, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, segment_map_composer<SourceRef, Id, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef earley_parser<typename lxns_rtno<InputIterator, Id, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::tag_input, typename lxns_rtno<InputIterator, Id, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::tag_output, SourceRef, ContextKey, ContextValue, segment_map<SourceRef, Id, output_set_impl_choice>, serializer<segment_map<SourceRef, Id, output_set_impl_choice> >, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, segment_map_composer<SourceRef, Id, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#else
	struct lx_earley_parser: public earley_parser<typename lx_rtno<InputIterator, Id>::type::tag_input, typename lx_rtno<InputIterator, Id>::type::tag_output, SourceRef, segment_map<SourceRef, Id, output_set_impl_choice>, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, segment_map_composer<SourceRef, Id, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef earley_parser<typename lx_rtno<InputIterator, Id>::type::tag_input, typename lx_rtno<InputIterator, Id>::type::tag_output, SourceRef, segment_map<SourceRef, Id, output_set_impl_choice>, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, segment_map_composer<SourceRef, Id, output_set_impl_choice>, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::context_type context_type;
		typedef typename base_type::match match;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::composer composer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		lx_earley_parser(): base_type()
		{}
		lx_earley_parser(match input_match_, transformer gamma_, composer circ_): base_type(input_match_, gamma_, circ_)
		{}

		blackboard_set& operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const context_type &c, blackboard_set &result)
		{
			base_type::gamma.set(input_begin, input_end);
			return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end, c, result);
		}
	};

	//This is just for homogeneity
	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, typename Id, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lx_earley_parser_impl_selector
	{ typedef lx_earley_parser<InputIterator, SourceRef, ContextKey, ContextValue, Id, execution_state_set_impl_choice, output_set_impl_choice> type; };
} //namespace grapenlp

#endif /*GRAPENLP_LX_EARLEY_PARSER_H*/
