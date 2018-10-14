/*
 * GRAPE
 *
 * Copyright (C) 2004-2008 Université de Marne-la-Vallée <javier.sastre@univ-mlv.fr>
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

#ifndef GRAPE_LX_BREADTH_FIRST_PARSER_NO_OUTPUT_H
#define GRAPE_LX_BREADTH_FIRST_PARSER_NO_OUTPUT_H

#include <grape/breadth_first_parser_no_output.h>
#include <grape/segment_map_x_weight.h>
#include <grape/lx_rtno.h>

namespace grape
{
	template<typename InputIterator, typename SourceRef, typename Id, typename StateConstRefStackPool, assoc_container_impl_choice execution_state_set_impl_choice>
#ifdef TRACE
	struct lx_breadth_first_parser_no_output: public breadth_first_parser_no_output<typename lxns_rtno<InputIterator, Id>::type::tag_input, typename lxns_rtno<InputIterator, Id>::type::tag_output, SourceRef, StateConstRefStackPool, execution_state_set_impl_choice>
	{
		typedef breadth_first_parser_no_output<typename lxns_rtno<InputIterator, Id>::type::tag_input, typename lxns_rtno<InputIterator, Id>::type::tag_output, SourceRef, StateConstRefStackPool, execution_state_set_impl_choice> base_type;
#else
	struct lx_breadth_first_parser_no_output: public breadth_first_parser_no_output<typename lx_rtno<InputIterator, Id>::type::tag_input, typename lx_rtno<InputIterator, Id>::type::tag_output, SourceRef, StateConstRefStackPool, execution_state_set_impl_choice>
	{
		typedef breadth_first_parser_no_output<typename lx_rtno<InputIterator, Id>::type::tag_input, typename lx_rtno<InputIterator, Id>::type::tag_output, SourceRef, StateConstRefStackPool, execution_state_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::match match;

		lx_breadth_first_parser_no_output(): base_type()
		{}
		lx_breadth_first_parser_no_output(match input_match_): base_type(input_match_)
		{}

		bool operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end)
		{ return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end); }
	};

	template<typename InputIterator, typename SourceRef, typename Id, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lx_breadth_first_parser_no_output_impl_selector
	{};

	template<typename InputIterator, typename SourceRef, typename Id, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lx_breadth_first_parser_no_output_impl_selector<InputIterator, SourceRef, Id, ARRAYS, execution_state_set_impl_choice>
	{
#ifdef TRACE
		typedef lx_breadth_first_parser_no_output<InputIterator, SourceRef, Id, array_fake_pool<typename lxns_rtno<InputIterator, Id>::type::state_const_ref>, execution_state_set_impl_choice> type;
#else
		typedef lx_breadth_first_parser_no_output<InputIterator, SourceRef, Id, array_fake_pool<typename lx_rtno<InputIterator, Id>::type::state_const_ref>, execution_state_set_impl_choice> type;
#endif
	};

	template<typename InputIterator, typename SourceRef, typename Id, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lx_breadth_first_parser_no_output_impl_selector<InputIterator, SourceRef, Id, TRIE_STRINGS, execution_state_set_impl_choice>
	{
#ifdef TRACE
		typedef lx_breadth_first_parser_no_output<InputIterator, SourceRef, Id, trie_string_pool<typename lxns_rtno<InputIterator, Id>::type::state_const_ref>, execution_state_set_impl_choice> type;
#else
		typedef lx_breadth_first_parser_no_output<InputIterator, SourceRef, Id, trie_string_pool<typename lx_rtno<InputIterator, Id>::type::state_const_ref>, execution_state_set_impl_choice> type;
#endif
	};
} //namespace grape

#endif /*GRAPE_LX_BREADTH_FIRST_PARSER_NO_OUTPUT_H*/
