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

#ifndef GRAPENLP_UA_FPRTN_BREADTH_FIRST_EXPANDER_H
#define GRAPENLP_UA_FPRTN_BREADTH_FIRST_EXPANDER_H

#include <grapenlp/lexmask.h>
#include <grapenlp/a_fprtn_breadth_first_expander.h>

namespace grapenlp
{
	template<typename SourceRef, typename RTNOTagInput, sequence_impl_choice sic, assoc_container_impl_choice execution_state_set_impl_choice, assoc_container_impl_choice output_set_impl_choice>
	struct ua_fprtn_breadth_first_expander_impl_selector
	{
		typedef typename a_fprtn_breadth_first_expander_impl_selector<SourceRef, unichar, RTNOTagInput, sic, execution_state_set_impl_choice, output_set_impl_choice>::type type;

	private:
		ua_fprtn_breadth_first_expander_impl_selector()
		{}
	};
}

#endif /*GRAPENLP_UA_WFPRTN_BREADTH_FIRST_EXPANDER_H*/
