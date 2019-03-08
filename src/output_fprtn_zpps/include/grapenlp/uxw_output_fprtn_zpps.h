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

#ifndef GRAPENLP_UXW_OUTPUT_FPRTN_ZPPS_H
#define GRAPENLP_UXW_OUTPUT_FPRTN_ZPPS_H

#include <grapenlp/unichar.h>
#include <grapenlp/xw_output_fprtn_zpps.h>

namespace grapenlp
{
	template<typename ContextMask, typename SourceRef, typename Weight, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct uxw_output_fprtn_zpps
	{
		typedef typename xw_output_fprtn_zpps<ContextMask, SourceRef, unichar, Weight, RTNOTagInput, execution_state_set_impl_choice>::type type;

	private:
		uxw_output_fprtn_zpps()
		{}
	};
} //namespace grapenlp

#endif /*GRAPENLP_LUXW_OUTPUT_FPRTN_ZPPS_H*/
