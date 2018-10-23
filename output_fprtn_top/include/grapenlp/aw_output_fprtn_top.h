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

#ifndef GRAPENLP_AW_OUTPUT_FPRTN_TOP_H
#define GRAPENLP_AW_OUTPUT_FPRTN_TOP_H

#include <grapenlp/array_const_ref_x_weight.h>
#include <grapenlp/output_fprtn_top.h>

namespace grapenlp
{
	template<typename SourceRef, typename T, typename Weight, typename RTNOTagInput, assoc_container_impl_choice execution_state_set_impl_choice>
	struct aw_output_fprtn_top
	{
		typedef typename output_fprtn_top<SourceRef, array_const_ref_x_weight<T, Weight>, RTNOTagInput, execution_state_set_impl_choice>::type type;

	private:
		aw_output_fprtn_top()
		{}
	};
} //namespace grapenlp

#endif /*GRAPENLP_AW_OUTPUT_FPRTN_TOP_H*/
