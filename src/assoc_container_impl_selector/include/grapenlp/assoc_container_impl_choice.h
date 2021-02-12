/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@univ-mlv.fr>
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

#ifndef GRAPENLP_ASSOC_CONTAINER_IMPL_SELECTOR_H
#define GRAPENLP_ASSOC_CONTAINER_IMPL_SELECTOR_H

#include <set>
#include <grapenlp/lrb_tree_set.h>
#include <grapenlp/lrb_tree_set_3w.h>

namespace grapenlp
{
	enum assoc_container_impl_choice {STD, LRB_TREE, LRB_TREE_3W};
	struct assoc_container_default_comparator_choice
	{};
} //namespace grapenlp

#endif /*GRAPENLP_ASSOC_CONTAINER_IMPL_SELECTOR_H*/
