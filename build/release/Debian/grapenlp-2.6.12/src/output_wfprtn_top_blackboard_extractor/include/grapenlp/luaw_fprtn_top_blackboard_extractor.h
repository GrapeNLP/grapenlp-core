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

#ifndef GRAPENLP_LUAW_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H
#define GRAPENLP_LUAW_FPRTN_TOP_BLACKBOARD_EXTRACTOR_H

#include <grapenlp/lexmask.h>
#include <grapenlp/uaw_fprtn_top_blackboard_extractor.h>

namespace grapenlp
{
	template<typename SourceRef, typename WeightTransformer, typename InputIterator, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice>
	struct luaw_fprtn_top_blackboard_extractor_impl_selector
	{
		typedef typename uaw_fprtn_top_blackboard_extractor_impl_selector<SourceRef, WeightTransformer, typename lexmask<InputIterator>::const_ref, sic, execution_state_set_impl_choice>::type type;

	private:
		luaw_fprtn_top_blackboard_extractor_impl_selector()
		{}
	};
}

#endif /*GRAPENLP_LUAW_WFPRTN_TOP_BLACKBOARD_EXTRACTOR_H*/
