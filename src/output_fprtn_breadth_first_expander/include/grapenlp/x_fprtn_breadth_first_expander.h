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

#ifndef GRAPENLP_X_FPRTN_BREADTH_FIRST_EXPANDER_H
#define GRAPENLP_X_FPRTN_BREADTH_FIRST_EXPANDER_H

#include <grapenlp/segment.h>
#include <grapenlp/x_output_fprtn.h>
#include <grapenlp/fprtn_breadth_first_expander.h>

namespace grapenlp
{
	template<typename SourceRef, typename Id, typename RTNOTagInput, typename StateConstRefStackPool, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
#ifdef TRACE
	struct x_fprtn_breadth_first_expander: public fprtn_breadth_first_expander<SourceRef, typename x_output_fprtn<SourceRef, Id, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map<SourceRef, Id, output_set_impl_choice>, serializer<segment_map<SourceRef, Id, output_set_impl_choice> >, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef fprtn_breadth_first_expander<SourceRef, typename x_output_fprtn<SourceRef, Id, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map<SourceRef, Id, output_set_impl_choice>, serializer<segment_map<SourceRef, Id, output_set_impl_choice> >, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#else
	struct x_fprtn_breadth_first_expander: public fprtn_breadth_first_expander<SourceRef, typename x_output_fprtn<SourceRef, Id, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map<SourceRef, Id, output_set_impl_choice>, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef fprtn_breadth_first_expander<SourceRef, typename x_output_fprtn<SourceRef, Id, RTNOTagInput, execution_state_set_impl_choice>::type::tag_input, RTNOTagInput, segment_map<SourceRef, Id, output_set_impl_choice>, segment_map_transformer<SourceRef, Id, output_set_impl_choice>, StateConstRefStackPool, execution_state_set_impl_choice, output_set_impl_choice> base_type;
#endif
		typedef typename base_type::machine machine;
		typedef typename base_type::tag_input tag_input;
		typedef typename base_type::source_ref source_ref;
		typedef typename base_type::transformer transformer;
		typedef typename base_type::blackboard blackboard;
		typedef typename base_type::blackboard_set blackboard_set;

		blackboard_set& operator() (const machine& m, source_ref input_begin, source_ref input_end, blackboard_set &result)
		{
			base_type::gamma.set(input_begin, input_end);
			return base_type::operator()(m, result);
		}
	};

	template<typename SourceRef, typename Id, typename RTNOTagInput, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct x_fprtn_breadth_first_expander_impl_selector
	{};

	template<typename SourceRef, typename Id, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct x_fprtn_breadth_first_expander_impl_selector<SourceRef, Id, RTNOTagInput, ARRAYS, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef x_fprtn_breadth_first_expander<SourceRef, Id, RTNOTagInput, array_fake_ref_pool<typename x_output_fprtn<SourceRef, Id, RTNOTagInput, execution_state_set_impl_choice>::type::state_const_ref>, execution_state_set_impl_choice, output_set_impl_choice> type;
	};

	template<typename SourceRef, typename Id, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct x_fprtn_breadth_first_expander_impl_selector<SourceRef, Id, RTNOTagInput, TRIE_STRINGS, execution_state_set_impl_choice, output_set_impl_choice>
	{
		typedef x_fprtn_breadth_first_expander<SourceRef, Id, RTNOTagInput, trie_string_ref_pool<typename x_output_fprtn<SourceRef, Id, RTNOTagInput, execution_state_set_impl_choice>::type::state_const_ref>, execution_state_set_impl_choice, output_set_impl_choice> type;
	};
}

#endif /*GRAPENLP_X_WFPRTN_BREADTH_FIRST_EXPANDER_H*/
