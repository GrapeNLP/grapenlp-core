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

#ifndef GRAPENLP_LXW_EARLEY_PARSER_NO_OUTPUT_H
#define GRAPENLP_LXW_EARLEY_PARSER_NO_OUTPUT_H

#include <grapenlp/earley_parser_no_output.h>
#include <grapenlp/lxw_rtno.h>

namespace grapenlp
{
	template<typename InputIterator, typename SourceRef, typename Id, typename Weight, assoc_container_impl_choice execution_state_set_impl_choice>
#ifdef TRACE
	struct lxw_earley_parser_no_output: public earley_parser_no_output<
	        typename lxwns_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_input,
	        typename lxwns_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_output,
	        SourceRef,
	        execution_state_set_impl_choice
	        >
	{
		typedef earley_parser_no_output<
				typename lxwns_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_input,
				typename lxwns_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_output,
				SourceRef,
				execution_state_set_impl_choice
		        > base_type;
#else
	struct lxw_earley_parser_no_output: public earley_parser_no_output<
	        typename lxw_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_input,
	        typename lxw_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_output,
	        SourceRef,
	        execution_state_set_impl_choice
	        >
	{
		typedef earley_parser_no_output<
				typename lxw_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_input,
				typename lxw_rtno<InputIterator, Id, Weight, u_context_mask>::type::tag_output,
				SourceRef,
				execution_state_set_impl_choice
		        > base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
typedef typename base_type::match match;

		lxw_earley_parser_no_output(): base_type()
		{}
		lxw_earley_parser_no_output(match input_match_): base_type(input_match_)
		{}

		bool operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const u_context &c)
		{ return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end, c); }
	};

	//This is just for homogeneity
	template<typename InputIterator, typename SourceRef, typename Id, typename Weight, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lxw_earley_parser_no_output_impl_selector
	{ typedef lxw_earley_parser_no_output<InputIterator, SourceRef, Id, Weight, execution_state_set_impl_choice> type; };
} //namespace grapenlp

#endif /*GRAPENLP_LXW_EARLEY_PARSER_NO_OUTPUT_H*/
