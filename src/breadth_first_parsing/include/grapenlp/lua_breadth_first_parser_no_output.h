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

#ifndef GRAPENLP_LUA_BREADTH_FIRST_PARSER_NO_OUTPUT_H
#define GRAPENLP_LUA_BREADTH_FIRST_PARSER_NO_OUTPUT_H

#include <grapenlp/lua_rtno.h>
#include <grapenlp/breadth_first_parser_no_output.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, typename StateConstRefStackPool, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lua_breadth_first_parser_no_output: public breadth_first_parser_no_output<typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value>::type::tag_input, typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value>::type::tag_output, SourceRef, ContextKey, ContextValue, StateConstRefStackPool, execution_state_set_impl_choice>
	{
		typedef breadth_first_parser_no_output<
		        typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value>::type::tag_input,
		        typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value>::type::tag_output,
		        SourceRef,
		        ContextKey,
		        ContextValue,
		        StateConstRefStackPool,
		        execution_state_set_impl_choice
		        > base_type;
#else
	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, typename StateConstRefStackPool, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lua_breadth_first_parser_no_output: public breadth_first_parser_no_output<
	        typename lua_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value>::type::tag_input,
	        typename lua_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_context_key, typename context<ContextKey, ContextValue>::optimized_context_value>::type::tag_output,
	        SourceRef,
	        ContextKey,
	        ContextValue,
	        StateConstRefStackPool,
	        execution_state_set_impl_choice>
	{
		typedef breadth_first_parser_no_output<typename lua_rtno<InputIterator>::type::tag_input, typename lua_rtno<InputIterator>::type::tag_output, SourceRef, StateConstRefStackPool, execution_state_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::context_type context_type;
		typedef typename base_type::match match;

		lua_breadth_first_parser_no_output(): base_type()
		{}
		lua_breadth_first_parser_no_output(match input_match_): base_type(input_match_)
		{}

		bool operator() (const machine& m, source_ref input_begin, source_ref input_end, bool hasnt_white_at_begin, bool hasnt_white_at_end, const context_type &c)
		{ return base_type::operator()(m, input_begin, input_end, hasnt_white_at_begin, hasnt_white_at_end, c); }
	};

	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lua_breadth_first_parser_no_output_impl_selector
	{};

	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lua_breadth_first_parser_no_output_impl_selector<InputIterator, SourceRef, ContextKey, ContextValue, ARRAYS, execution_state_set_impl_choice>
	{
#ifdef TRACE
		typedef lua_breadth_first_parser_no_output<InputIterator, SourceRef, ContextKey, ContextValue, array_fake_pool<typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::state_const_ref>, execution_state_set_impl_choice> type;
#else
		typedef lua_breadth_first_parser_no_output<InputIterator, SourceRef, ContextKey, ContextValue, array_fake_pool<typename lua_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::state_const_ref>, execution_state_set_impl_choice> type;
#endif
	};

	template<typename InputIterator, typename SourceRef, typename ContextKey, typename ContextValue, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lua_breadth_first_parser_no_output_impl_selector<InputIterator, SourceRef, ContextKey, ContextValue, TRIE_STRINGS, execution_state_set_impl_choice>
	{
#ifdef TRACE
		typedef lua_breadth_first_parser_no_output<InputIterator, SourceRef, ContextKey, ContextValue, trie_string_pool<typename luans_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::state_const_ref>, execution_state_set_impl_choice> type;
#else
		typedef lua_breadth_first_parser_no_output<InputIterator, SourceRef, ContextKey, ContextValue, trie_string_pool<typename lua_rtno<InputIterator, typename context<ContextKey, ContextValue>::optimized_key, typename context<ContextKey, ContextValue>::optimized_value>::type::state_const_ref>, execution_state_set_impl_choice> type;
#endif
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUA_BREADTH_FIRST_PARSER_NO_OUTPUT_H*/
