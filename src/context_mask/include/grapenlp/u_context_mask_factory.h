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

#ifndef GRAPENLP_UL_CONTEXT_MASK_FACTORY_H
#define GRAPENLP_UL_CONTEXT_MASK_FACTORY_H

#include <grapenlp/u_array.h>
#include <grapenlp/u_context_mask.h>
#include <grapenlp/u_context_mask_constants.h>

namespace grapenlp
{
    u_context_mask* make_u_context_mask(u_array::const_iterator context_expression_begin, u_array::const_iterator context_expression_end, u_context_key_value_hasher &c_hasher);
} //namespace grapenlp

#endif /*GRAPENLP_UL_CONTEXT_MASK_FACTORY_H*/
