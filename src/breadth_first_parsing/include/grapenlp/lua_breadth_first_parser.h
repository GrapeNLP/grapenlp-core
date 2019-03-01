/*
 * GRAPENLP
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

#ifndef GRAPENLP_LUA_BREADTH_FIRST_PARSER_H
#define GRAPENLP_LUA_BREADTH_FIRST_PARSER_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

#include <grapenlp/lua_rtno.h>
#include <grapenlp/breadth_first_parser.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, typename StateConstRefStackPool, typename OutputUArrayPool, typename OutputUArraySerializer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lua_breadth_first_parser: public breadth_first_parser<
	        typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::tag_input,
	        typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::tag_output,
	        SourceRef,
	        ContextKey,
	        ContextValue,
	        typename OutputUArrayPool::value_type,
	        OutputUArraySerializer,
	        typename OutputUArrayPool::concatenator,
	        StateConstRefStackPool,
	        execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef breadth_first_parser<typename luans_rtno<InputIterator>::type::tag_input, typename luans_rtno<InputIterator>::type::tag_output, SourceRef, typename OutputUArrayPool::value_type, OutputUArraySerializer, typename OutputUArrayPool::concatenator, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#else
	template<typename InputIterator, typename SourceRef, typename StateConstRefStackPool, typename OutputUArrayPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lua_breadth_first_parser: public breadth_first_parser<typename lua_rtno<InputIterator>::type::tag_input, typename lua_rtno<InputIterator>::type::tag_output, SourceRef, typename OutputUArrayPool::value_type, typename OutputUArrayPool::concatenator, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef breadth_first_parser<typename lua_rtno<InputIterator>::type::tag_input, typename lua_rtno<InputIterator>::type::tag_output, SourceRef, typename OutputUArrayPool::value_type, typename OutputUArrayPool::concatenator, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;

		typedef ContextKeyIterator context_key_iterator;
		typedef ContextValueIterator context_value_iterator;
		typedef context<context_key_iterator, context_value_iterator> context_type;
		typedef typename context_type::optimized_key context_key;
		typedef typename context_type::optimized_value context_value;

		typedef typename base_type::match match;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		lua_breadth_first_parser(): base_type()
		{}
		lua_breadth_first_parser(match input_match_, transformer gamma_): base_type(input_match_, gamma_)
		{}
	};

	template<typename InputIterator, typename SourceRef, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lua_breadth_first_parser_impl_selector
	{};

	template<typename InputIterator, typename SourceRef, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lua_breadth_first_parser_impl_selector<InputIterator, SourceRef, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>
	{
#ifdef TRACE
		typedef lua_breadth_first_parser<InputIterator, SourceRef, array_fake_pool<typename luans_rtno<InputIterator>::type::state_const_ref>, array_fake_pool<unichar>, serializer<array_fake_pool<unichar>::value_type>, execution_state_set_impl_choice, output_set_impl_choice> type;
#else
		typedef lua_breadth_first_parser<InputIterator, SourceRef, array_fake_pool<typename lua_rtno<InputIterator>::type::state_const_ref>, array_fake_pool<unichar>, execution_state_set_impl_choice, output_set_impl_choice> type;
#endif
	};

	template<typename InputIterator, typename SourceRef, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct lua_breadth_first_parser_impl_selector<InputIterator, SourceRef, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>
	{
#ifdef TRACE
		typedef lua_breadth_first_parser<InputIterator, SourceRef, trie_string_pool<typename luans_rtno<InputIterator>::type::state_const_ref>, trie_string_ref_pool<unichar>, const_deref_serializer<typename trie_string_ref_pool<unichar>::base_type>, execution_state_set_impl_choice, output_set_impl_choice> type;
#else
		typedef lua_breadth_first_parser<InputIterator, SourceRef, trie_string_pool<typename lua_rtno<InputIterator>::type::state_const_ref>, trie_string_ref_pool<unichar>, execution_state_set_impl_choice, output_set_impl_choice> type;
#endif
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUA_BREADTH_FIRST_PARSER_H*/
