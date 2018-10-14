/*
 * GRAPE
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

#ifndef GRAPE_LUAW_OUTPUT_FPRTN_TOP_H
#define GRAPE_LUAW_OUTPUT_FPRTN_TOP_H

#include <grape/lexmask.h>
#include <grape/uaw_output_fprtn_top.h>

namespace grape
{
	template<typename SourceRef, typename Weight, typename InputIterator, assoc_container_impl_choice execution_state_set_impl_choice>
	struct luaw_output_fprtn_top
	{
		typedef typename uaw_output_fprtn_top<SourceRef, Weight, typename lexmask<InputIterator>::const_ref, execution_state_set_impl_choice>::type type;

	private:
		luaw_output_fprtn_top()
		{}
	};
} //namespace grape

#endif /*GRAPE_LUAW_OUTPUT_FPRTN_TOP_H*/
