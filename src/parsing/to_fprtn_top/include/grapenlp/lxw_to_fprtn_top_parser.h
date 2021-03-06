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

#ifndef GRAPENLP_LXW_TO_FPRTN_TOP_PARSER_H
#define GRAPENLP_LXW_TO_FPRTN_TOP_PARSER_H

#include <grapenlp/lxw_rtno.h>
#include <grapenlp/to_fprtn_top_parser.h>

namespace grapenlp
{
	template<typename InputIterator, typename SourceRef, typename Id, typename Weight, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lxw_to_fprtn_top_parser_impl_selector
	{
		typedef to_fprtn_top_parser<
		        typename lxw_rtno<InputIterator, Id, Weight, u_context_mask>::tag_input,
		        typename lxw_rtno<InputIterator, Id, Weight, u_context_mask>::tag_output,
		        SourceRef,
		        execution_state_set_impl_choice
		        > type;
	};
} //namespace grapenlp

#endif /*GRAPENLP_LXW_TO_FPRTN_TOP_PARSER_H*/
