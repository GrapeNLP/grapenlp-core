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

#ifndef GRAPENLP_LX_DEPTH_FIRST_PARSER_NO_OUTPUT_H
#define GRAPENLP_LX_DEPTH_FIRST_PARSER_NO_OUTPUT_H

#include <grapenlp/segment.h>
#include <grapenlp/lx_rtno.h>
#include <grapenlp/depth_first_parser_no_output.h>

namespace grapenlp
{
	template<typename InputIterator, typename SourceRef, typename Id, typename StateConstRefStackPool>
#ifdef TRACE
	struct lx_depth_first_parser_no_output: public depth_first_parser_no_output<
	        typename lxns_rtno<InputIterator, Id, u_context_mask>::tag_input,
	        typename lx_rtno<InputIterator, Id, u_context_mask>::tag_output,
	        SourceRef,
	        StateConstRefStackPool
	        >
	{
		typedef depth_first_parser_no_output<
                typename lxns_rtno<InputIterator, Id, u_context_mask>::tag_input,
                typename lx_rtno<InputIterator, Id, u_context_mask>::tag_output,
                SourceRef,
                StateConstRefStackPool
                > base_type;
#else
	struct lx_depth_first_parser_no_output: public depth_first_parser_no_output<
	        typename lx_rtno<InputIterator, Id, u_context_mask>::tag_input,
	        typename lx_rtno<InputIterator, Id, u_context_mask>::tag_output,
	        SourceRef,
	        StateConstRefStackPool
	        >
	{
		typedef depth_first_parser_no_output<
				typename lx_rtno<InputIterator, Id, u_context_mask>::tag_input,
				typename lx_rtno<InputIterator, Id, u_context_mask>::tag_output,
				SourceRef,
				StateConstRefStackPool
				> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
typedef typename base_type::match match;

		lx_depth_first_parser_no_output(): base_type()
		{}
		lx_depth_first_parser_no_output(match input_match_): base_type(input_match_)
		{}

		bool operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const u_context &c)
		{ return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end, c); }
	};

	template<typename InputIterator, typename SourceRef, typename Id, sequence_impl_choice sic>
	struct lx_depth_first_parser_no_output_impl_selector
	{};

	template<typename InputIterator, typename SourceRef, typename Id>
	struct lx_depth_first_parser_no_output_impl_selector<InputIterator, SourceRef, Id, ARRAYS>
	{
#ifdef TRACE
		typedef lx_depth_first_parser_no_output<InputIterator, SourceRef, Id, array_fake_pool<typename lxns_rtno<InputIterator, Id, u_context_mask>::state_const_ref> > type;
#else
		typedef lx_depth_first_parser_no_output<InputIterator, SourceRef, Id, array_fake_pool<typename lx_rtno<InputIterator, Id, u_context_mask>::state_const_ref> > type;
#endif
	};

	template<typename InputIterator, typename SourceRef, typename Id>
	struct lx_depth_first_parser_no_output_impl_selector<InputIterator, SourceRef, Id, TRIE_STRINGS>
	{
#ifdef TRACE
		typedef lx_depth_first_parser_no_output<InputIterator, SourceRef, Id, trie_string_pool<typename lxns_rtno<InputIterator, Id, u_context_mask>::state_const_ref> > type;
#else
		typedef lx_depth_first_parser_no_output<InputIterator, SourceRef, Id, trie_string_pool<typename lx_rtno<InputIterator, Id, u_context_mask>::state_const_ref> > type;
#endif
	};
} //namespace grapenlp

#endif /*GRAPENLP_LX_DEPTH_FIRST_PARSER_NO_OUTPUT_H*/
