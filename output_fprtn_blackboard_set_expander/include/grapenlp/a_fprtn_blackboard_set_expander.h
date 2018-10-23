/*
 * GRAPENLP
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

#ifndef GRAPENLP_A_FPRTN_BLACKBOARD_SET_EXPANDER_H
#define GRAPENLP_A_FPRTN_BLACKBOARD_SET_EXPANDER_H

#ifdef TRACE
#include <grapenlp/iostream.h>
#endif

#include <grapenlp/pool.h>
#include <grapenlp/a_output_fprtn_zpps.h>
#include <grapenlp/fprtn_blackboard_set_expander.h>

namespace grapenlp
{
#ifdef TRACE
	template<typename SourceRef, typename RTNOTagInput, typename OutputArrayPool, typename OutputArraySerializer, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct a_fprtn_blackboard_set_expander: public fprtn_blackboard_set_expander<SourceRef, typename a_output_fprtn_zpps<SourceRef, typename OutputArrayPool::char_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, typename OutputArrayPool::value_type, OutputArraySerializer, typename OutputArrayPool::concatenator, typename OutputArrayPool::concatenator2, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef fprtn_blackboard_set_expander<SourceRef, typename a_output_fprtn_zpps<SourceRef, typename OutputArrayPool::char_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, typename OutputArrayPool::value_type, OutputArraySerializer, typename OutputArrayPool::concatenator, typename OutputArrayPool::concatenator2, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#else
	template<typename SourceRef, typename RTNOTagInput, typename OutputArrayPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct a_fprtn_blackboard_set_expander: public fprtn_blackboard_set_expander<SourceRef, typename a_output_fprtn_zpps<SourceRef, typename OutputArrayPool::char_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, typename OutputArrayPool::value_type, typename OutputArrayPool::concatenator, typename OutputArrayPool::concatenator2, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef fprtn_blackboard_set_expander<SourceRef, typename a_output_fprtn_zpps<SourceRef, typename OutputArrayPool::char_type, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, typename OutputArrayPool::value_type, typename OutputArrayPool::concatenator, typename OutputArrayPool::concatenator2, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::tag_input tag_input;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		a_fprtn_blackboard_set_expander(): base_type()
		{}
		a_fprtn_blackboard_set_expander(transformer gamma_): base_type(gamma_)
		{}
	};

	template<typename SourceRef, typename OutputChar, typename RTNOTagInput, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct a_fprtn_blackboard_set_expander_impl_selector
	{};

	template<typename SourceRef, typename OutputChar, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct a_fprtn_blackboard_set_expander_impl_selector<SourceRef, OutputChar, RTNOTagInput, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>
	{
#ifdef TRACE
		typedef a_fprtn_blackboard_set_expander<SourceRef, RTNOTagInput, array_fake_pool<OutputChar>, serializer<typename array_fake_pool<OutputChar>::value_type>, execution_state_set_impl_choice, output_set_impl_choice> type;
#else
		typedef a_fprtn_blackboard_set_expander<SourceRef, RTNOTagInput, array_fake_pool<OutputChar>, execution_state_set_impl_choice, output_set_impl_choice> type;
#endif
	};

	template<typename SourceRef, typename OutputChar, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct a_fprtn_blackboard_set_expander_impl_selector<SourceRef, OutputChar, RTNOTagInput, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>
	{
#ifdef TRACE
		typedef a_fprtn_blackboard_set_expander<SourceRef, RTNOTagInput, trie_string_ref_pool<OutputChar>, const_deref_serializer<typename trie_string_ref_pool<OutputChar>::base_type>, execution_state_set_impl_choice, output_set_impl_choice> type;
#else
		typedef a_fprtn_blackboard_set_expander<SourceRef, RTNOTagInput, trie_string_ref_pool<OutputChar>, execution_state_set_impl_choice, output_set_impl_choice> type;
#endif
	};
}

#endif /*GRAPENLP_A_WFPRTN_BLACKBOARD_SET_EXPANDER_H*/
