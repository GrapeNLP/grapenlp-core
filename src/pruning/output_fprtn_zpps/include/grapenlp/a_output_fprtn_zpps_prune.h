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

#ifndef GRAPENLP_A_OUTPUT_FPRTN_ZPPS_PRUNE_H
#define GRAPENLP_A_OUTPUT_FPRTN_ZPPS_PRUNE_H

#include <grapenlp/output_fprtn_zpps_prune.h>
#include <grapenlp/a_output_fprtn_zpps.h>

namespace grapenlp
{
	template<typename SourceRef, typename T, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	std::size_t a_prune_zpps(a_output_fprtn_zpps<u_context_mask, SourceRef, T, RTNOTagInput, execution_state_set_impl_choice> &m)
	{
		return prune_zpps<SourceRef, const array<T> *, RTNOTagInput, execution_state_set_impl_choice>(m);
	}
} //namespace grapenlp

#endif /*GRAPENLP_A_OUTPUT_FPRTN_ZPPS_PRUNE_H*/
