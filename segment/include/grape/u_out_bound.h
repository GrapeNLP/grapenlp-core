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

#ifndef GRAPE_U_OUT_BOUND_H
#define GRAPE_U_OUT_BOUND_H

#include <grape/unicode.h>
#include <grape/out_bound.h>

namespace grape
{
	typedef out_bound<unichar> u_out_bound;
	typedef u_out_bound::ref u_out_bound_ref;
	typedef u_out_bound::const_ref u_out_bound_const_ref;
	typedef u_out_bound::trie u_out_bound_trie;
	typedef u_out_bound_trie::string u_out_bound_trie_string;
	typedef u_out_bound_trie_string::ref u_out_bound_trie_string_ref;
	typedef out_bound_const_ref_triplet<unichar> u_out_bound_const_ref_triplet;
} //namespace grape

#endif /*GRAPE_U_OUT_BOUND_H_*/
