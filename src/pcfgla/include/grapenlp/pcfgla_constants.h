/*
 * GRAPENLP
 *
 * Copyright (C) 2011 Universidad de Alicante <javier.sastre@gmail.com>
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

#ifndef GRAPENLP_PCFGLA_CONSTANTS_H
#define GRAPENLP_PCFGLA_CONSTANTS_H

#include <array>

#include <grapenlp/unicode.h>

namespace grapenlp
{
	const unichar bar_n_term_first_label_char = '@';
	const std::array<unichar, 4> default_axiom_label = { {'R', 'O', 'O', 'T'} };
	const unsigned int default_axiom_idx = 0;
	const bool default_axiom_is_pos = true;
} //namespace grapenlp

#endif /*GRAPENLP_PCFGLA_CONSTANTS_H*/
