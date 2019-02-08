/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2008 Université de Marne-la-Vallée <javier.sastre@univ-mlv.fr>
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

#ifndef GRAPENLP_U_DELAF_ENTRY_FILTER_CODES_H
#define GRAPENLP_U_DELAF_ENTRY_FILTER_CODES_H

#include <array>

#include <grapenlp/unicode.h>

namespace grapenlp
{
	const unichar negation_symbol = '!';
	const unichar mandatory_semantic_trait_mark = '+';
	const unichar forbidden_semantic_trait_mark = '-';

	const std::array<unichar, 3> true_delaf_entry_filter_code = { {'D', 'I', 'C' } };
	const std::array<unichar, 4> false_delaf_entry_filter_code = { {'!', 'D', 'I', 'C' } };
} //namespace grapenlp

#endif /*GRAPENLP_U_DELAF_ENTRY_FILTER_CODES_H*/
