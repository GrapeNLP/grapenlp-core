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

#ifndef GRAPENLP_UL_TAG_INPUT_CONSTANTS_H
#define GRAPENLP_UL_TAG_INPUT_CONSTANTS_H

#include <grapenlp/u_context_mask_constants.h>
#include <grapenlp/u_lexmask_constants.h>

const unichar in_out_separator_char = '/';
const std::array<unichar, 4> epsilon_transition_code = { {'%', '<', 'E', '>'} };
const std::array<unichar, 2> blank_epsilon_transition_code = { {'%', ' '} };
const std::array<unichar, 2> no_blank_epsilon_transition_code = { {'%', '#'} };

#endif //GRAPENLP_UL_TAG_INPUT_CONSTANTS_H
