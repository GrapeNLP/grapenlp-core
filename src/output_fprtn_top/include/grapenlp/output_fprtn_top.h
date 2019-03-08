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

#ifndef GRAPENLP_OUTPUT_FPRTN_TOP_H
#define GRAPENLP_OUTPUT_FPRTN_TOP_H

#include <grapenlp/weighted_tag_output_traits.h>
#include <grapenlp/output_fprtn.h>

namespace grapenlp
{
	enum output_fprtn_reverse_transition_type {OUTPUT_FPRTN_REVERSE_POP_TRANSITION_TYPE, OUTPUT_FPRTN_REVERSE_PUSH_TRANSITION_TYPE, OUTPUT_FPRTN_REVERSE_EPSILON_TRANSITION_TYPE, OUTPUT_FPRTN_REVERSE_CONSUMING_TRANSITION_TYPE};

	template<typename TagInput>
	struct top_data_x_incoming_filtered_pop_transition_counter
	{
		typedef TagInput tag_input;
		typedef typename weighted_tag_output_traits<tag_input>::weight weight;
		//The part of the consuming transition tag that is not the weight:
		typedef typename weighted_tag_output_traits<tag_input>::non_weight non_weight;

		weight top_w;
		//This is void since otherwise there would be a recursive type definition; a static_cast<state_ref>(r_t) will be performed before using this field
		void* top_r_t;
		void* top_r_c;
		non_weight top_non_w;
		output_fprtn_reverse_transition_type top_reverse_transition_type;
		std::size_t ifptc;

		top_data_x_incoming_filtered_pop_transition_counter()
		{}

		//Avoid wasting time copying this info since it will be initialized and modified in the ultimate copy only
		top_data_x_incoming_filtered_pop_transition_counter(__attribute__((unused)) const top_data_x_incoming_filtered_pop_transition_counter &tdxincoming_transition_count)
		{}
	};

	template<typename ContextMask, typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct output_fprtn_top
	{
		typedef output_fprtn<
			ContextMask,
			SourceRef,
			TagInput,
			RTNOTagInput,
			execution_state_set_impl_choice,
			ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA,
			top_data_x_incoming_filtered_pop_transition_counter<TagInput>
			> type;
	};
}

#endif /*GRAPENLP_OUTPUT_FPRTN_TOP_H*/
