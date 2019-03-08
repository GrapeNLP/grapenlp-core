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

#ifndef GRAPENLP_OUTPUT_FPRTN_ZPPS_H
#define GRAPENLP_OUTPUT_FPRTN_ZPPS_H

#include <grapenlp/output_fprtn.h>

namespace grapenlp
{
	struct index_x_incoming_filtered_pop_transition_counter
	{
		std::size_t idx;
		std::size_t ifptc;
		//Without these useless data fields, the performance is decreased!!
		//No idea why this is so, maybe the compiler skips some optimization
		//if these fields are not present, maybe the extra size of this struct
		//allows their instantiations to follow some memory alignment...
		//Anyway, these fields are not initialized, as for fields idx and ifptc,
		//just memory is allocated for holding all these fields, then only fields
		//idx and ifptc are filled with the required data only for useless
		//FPRTN states while pruning the FPRTN
		std::size_t useless_data_1;
		std::size_t useless_data_2;
		std::size_t useless_data_3;
		std::size_t useless_data_4;

		index_x_incoming_filtered_pop_transition_counter()
		{}

		//Avoid wasting time copying this info since it will be initialized and modified in the ultimate copy only
		index_x_incoming_filtered_pop_transition_counter(__attribute__((unused)) const index_x_incoming_filtered_pop_transition_counter &bsixifptc)
		{}
	};

	template<typename ContextMask, typename SourceRef, typename TagInput, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct output_fprtn_zpps
	{
		typedef output_fprtn<
			ContextMask,
		    SourceRef,
			TagInput,
			RTNOTagInput,
			execution_state_set_impl_choice,
			ZPPS_ITERATOR_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA,
			index_x_incoming_filtered_pop_transition_counter
			> type;
	};
}

#endif /*GRAPENLP_OUTPUT_FPRTN_ZPPS_H*/
