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

#ifndef GRAPENLP_LUAW_FPRTN_BLACKBOARD_SET_EXPANDER_H
#define GRAPENLP_LUAW_FPRTN_BLACKBOARD_SET_EXPANDER_H

#include <grapenlp/lexmask.h>
#include <grapenlp/uaw_fprtn_blackboard_set_expander.h>

namespace grapenlp
{
	template<typename SourceRef, typename WeightTransformer, typename InputIterator, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct luaw_fprtn_blackboard_set_expander_impl_selector
	{
		typedef typename uaw_fprtn_blackboard_set_expander_impl_selector<SourceRef, WeightTransformer, typename lexmask<InputIterator>::const_ref, sic, execution_state_set_impl_choice, output_set_impl_choice>::type type;

	private:
		luaw_fprtn_blackboard_set_expander_impl_selector()
		{}
	};
}

#endif /*GRAPENLP_LUAW_WFPRTN_BLACKBOARD_SET_EXPANDER_H*/
