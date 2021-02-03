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

#ifndef GRAPENLP_LUXW_OUTPUT_FPRTN_H
#define GRAPENLP_LUXW_OUTPUT_FPRTN_H

#include <grapenlp/lexmask.h>
#include <grapenlp/uxw_output_fprtn.h>

namespace grapenlp
{
	template<typename ContextMask, typename SourceRef, typename Weight, typename InputIterator, assoc_container_impl_choice execution_state_set_impl_choice, output_fprtn_incoming_filtered_pop_transition_extra_data_choice edc = NO_OUTPUT_FPRTN_INCOMING_FILTERED_POP_TRANSITION_EXTRA_DATA, typename StateMappedExtraData = empty_class>
	using luxw_output_fprtn = uxw_output_fprtn<ContextMask, SourceRef, Weight, typename lexmask<InputIterator>::const_ref, execution_state_set_impl_choice, edc, StateMappedExtraData>;
} //namespace grapenlp

#endif /*GRAPENLP_LUXW_OUTPUT_FPRTN_H*/
