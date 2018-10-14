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

#ifndef GRAPE_LUAW_TO_FPRTN_PARSER_H
#define GRAPE_LUAW_TO_FPRTN_PARSER_H

#include <grape/luaw_rtno.h>
#include <grape/to_fprtn_parser.h>

namespace grape
{
	template<typename InputIterator, typename SourceRef, typename Weight, assoc_container_impl_choice execution_state_set_impl_choice>
	struct luaw_to_fprtn_parser_impl_selector
	{
		typedef to_fprtn_parser<typename luaw_rtno<InputIterator, Weight>::type::tag_input, typename luaw_rtno<InputIterator, Weight>::type::tag_output, SourceRef, execution_state_set_impl_choice> type;

	private:
		//Constructor disabled; this is a typedef only struct
		luaw_to_fprtn_parser_impl_selector()
		{}
	};
} //namespace grape

#endif /*GRAPE_LUAW_TO_FPRTN_PARSER_H*/
