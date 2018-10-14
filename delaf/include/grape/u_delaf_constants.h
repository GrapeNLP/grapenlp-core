/*
 * GRAPE
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

#ifndef GRAPE_U_DELAF_CONSTANTS_H
#define GRAPE_U_DELAF_CONSTANTS_H

#include <array>

#include <grape/unicode.h>

namespace grape
{
	const unichar entry_separator = ',';
	const unichar lemma_separator = ',';
	const unichar canonical_form_separator = '.';
	const unichar semantic_traits_separator = '+';
	const unichar flexional_traits_separator = ':';
	const unichar clitic_pronouns_separator = '+';
	const unichar comment_separator = '/';
	const std::array<unichar, 3> known_word_meta_mask_code = { {'D', 'I', 'C'} };
	const std::array<unichar, 4> unknown_word_meta_mask_code = { {'!', 'D', 'I', 'C'} };
} //namespace grape

#endif /*GRAPE_U_DELAF_CONSTANTS_H*/
