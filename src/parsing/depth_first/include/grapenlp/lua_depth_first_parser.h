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

#ifndef GRAPENLP_LUA_DEPTH_FIRST_PARSER_H
#define GRAPENLP_LUA_DEPTH_FIRST_PARSER_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

#include <grapenlp/lua_rtno.h>
#include <grapenlp/depth_first_parser.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename InputIterator, typename SourceRef, typename StateConstRefStackPool, typename OutputUArrayPool, typename OutputUArraySerializer, assoc_container_impl_choice output_set_impl_choice>
	struct lua_depth_first_parser: public depth_first_parser<
	        typename luans_rtno<InputIterator, u_context_mask>::type::tag_input,
	        typename luans_rtno<InputIterator, u_context_mask>::type::tag_output,
	        SourceRef,
	        typename OutputUArrayPool::value_type,
	        OutputUArraySerializer,
	        typename OutputUArrayPool::concatenator,
	        StateConstRefStackPool,
	        output_set_impl_choice
	        >
	{
		typedef depth_first_parser<
				typename luans_rtno<InputIterator, u_context_mask>::type::tag_input,
				typename luans_rtno<InputIterator, u_context_mask>::type::tag_output,
				SourceRef,
				typename OutputUArrayPool::value_type,
				OutputUArraySerializer,
				typename OutputUArrayPool::concatenator,
				StateConstRefStackPool,
				output_set_impl_choice
				> base_type;
#else
	template<typename InputIterator, typename SourceRef, typename StateConstRefStackPool, typename OutputUArrayPool, assoc_container_impl_choice output_set_impl_choice>
	struct lua_depth_first_parser: public depth_first_parser<
	        typename lua_rtno<InputIterator, u_context_mask>::type::tag_input,
	        typename lua_rtno<InputIterator, u_context_mask>::type::tag_output,
	        SourceRef,
	        typename OutputUArrayPool::value_type,
	        typename OutputUArrayPool::concatenator,
	        StateConstRefStackPool,
	        output_set_impl_choice
	        >
	{
		typedef depth_first_parser<
                typename lua_rtno<InputIterator, u_context_mask>::type::tag_input,
                typename lua_rtno<InputIterator, u_context_mask>::type::tag_output,
                SourceRef,
                typename OutputUArrayPool::value_type,
                typename OutputUArrayPool::concatenator,
                StateConstRefStackPool,
                output_set_impl_choice
    			> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::match match;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		lua_depth_first_parser(): base_type()
		{}
		lua_depth_first_parser(match input_match_, transformer gamma_): base_type(input_match_, gamma_)
		{}
	};

	template<typename InputIterator, typename SourceRef, sequence_impl_choice sic, assoc_container_impl_choice output_set_impl_choice>
	struct lua_depth_first_parser_impl_selector
	{};

	template<typename InputIterator, typename SourceRef, assoc_container_impl_choice output_set_impl_choice>
	struct lua_depth_first_parser_impl_selector<InputIterator, SourceRef, ARRAYS, output_set_impl_choice>
	{
#ifdef TRACE
		typedef lua_depth_first_parser<InputIterator, SourceRef, array_fake_pool<typename luans_rtno<InputIterator, u_context_mask>::type::state_const_ref>, array_fake_pool<unichar>, serializer<array_fake_pool<unichar>::value_type>, output_set_impl_choice> type;
#else
		typedef lua_depth_first_parser<InputIterator, SourceRef, array_fake_pool<typename lua_rtno<InputIterator, u_context_mask>::type::state_const_ref>, array_fake_pool<unichar>, output_set_impl_choice> type;
#endif
	};

	template<typename InputIterator, typename SourceRef, assoc_container_impl_choice output_set_impl_choice>
	struct lua_depth_first_parser_impl_selector<InputIterator, SourceRef, TRIE_STRINGS, output_set_impl_choice>
	{
#ifdef TRACE
		typedef lua_depth_first_parser<InputIterator, SourceRef, trie_string_pool<typename luans_rtno<InputIterator, u_context_mask>::type::state_const_ref>, trie_string_ref_pool<unichar>, const_deref_serializer<typename trie_string_ref_pool<unichar>::base_type>, output_set_impl_choice> type;
#else
		typedef lua_depth_first_parser<InputIterator, SourceRef, trie_string_pool<typename lua_rtno<InputIterator, u_context_mask>::type::state_const_ref>, trie_string_ref_pool<unichar>, output_set_impl_choice> type;
#endif
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUA_DEPTH_FIRST_PARSER_H*/
