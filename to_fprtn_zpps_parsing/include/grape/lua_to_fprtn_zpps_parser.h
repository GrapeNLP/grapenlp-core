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

#ifndef GRAPE_LUA_TO_FPRTN_ZPPS_PARSER_H
#define GRAPE_LUA_TO_FPRTN_ZPPS_PARSER_H

#include <grape/lua_rtno.h>
#include <grape/to_fprtn_zpps_parser.h>

namespace grape
{
	template<typename InputIterator, typename SourceRef, assoc_container_impl_choice execution_state_set_impl_choice>
	struct lua_to_fprtn_zpps_parser_impl_selector
	{
		typedef to_fprtn_zpps_parser<typename lua_rtno<InputIterator>::type::tag_input, typename lua_rtno<InputIterator>::type::tag_output, SourceRef, execution_state_set_impl_choice> type;

	private:
		//Constructor disabled; this is a typedef only struct
		lua_to_fprtn_zpps_parser_impl_selector()
		{}
	};
} //namespace grape

#endif /*GRAPE_LUA_TO_FPRTN_ZPPS_PARSER_H*/
