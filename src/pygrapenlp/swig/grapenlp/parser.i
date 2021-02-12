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

/* parser.i */
%module parser

%{
#include <grapenlp/parser.h>
%}

namespace grapenlp
{
	enum rtno_parser_type
	{
		DEPTH_FIRST_RTNO_PARSER,
		BREADTH_FIRST_RTNO_PARSER,
		EARLEY_RTNO_PARSER,
		TO_FPRTN_RTNO_PARSER,
		TO_FPRTN_ZPPS_RTNO_PARSER,
		TO_FPRTN_TOP_RTNO_PARSER,
		TO_FPRTN_AND_BREADTH_FIRST_EXPAND_RTNO_PARSER,
		TO_FPRTN_AND_BLACKBOARD_SET_EXPAND_RTNO_PARSER,
		TO_FPRTN_AND_TOP_BLACKBOARD_EXTRACT_RTNO_PARSER
	};
}
