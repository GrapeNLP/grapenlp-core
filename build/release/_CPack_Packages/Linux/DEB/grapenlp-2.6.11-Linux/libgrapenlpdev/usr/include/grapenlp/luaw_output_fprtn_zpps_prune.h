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

#ifndef GRAPENLP_LUAW_OUTPUT_FPRTN_ZPPS_PRUNE_H
#define GRAPENLP_LUAW_OUTPUT_FPRTN_ZPPS_PRUNE_H

#include <grapenlp/uaw_output_fprtn_zpps_prune.h>
#include <grapenlp/luaw_output_fprtn_zpps.h>

namespace grapenlp
{
	template<typename SourceRef, typename Weight, typename InputIterator, assoc_container_impl_choice execution_state_set_impl_choice>
	std::size_t luaw_prune_zpps(typename luaw_output_fprtn_zpps<SourceRef, Weight, InputIterator, execution_state_set_impl_choice>::type &m)
	{
		return uaw_prune_zpps<SourceRef, Weight, typename lexmask<InputIterator>::const_ref, execution_state_set_impl_choice>(m);
	}
} //namespace grapenlp

#endif /*GRAPENLP_LUAW_OUTPUT_FPRTN_ZPPS_PRUNE_H*/
