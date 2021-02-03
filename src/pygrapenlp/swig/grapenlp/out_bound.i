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

/* out_bound.i */
%module out_bound
%include<trie_with_ptr_data.i>
%{
#include <grapenlp/out_bound.h>
%}

namespace grapenlp
{
    struct out_bound_const_ref_triplet;

    %nodefaultctor out_bound;
    %nodefaultdtor out_bound;
	template<typename T>
	struct out_bound
    {
		typedef out_bound* ref;
		typedef out_bound const * const_ref;
		typedef trie_with_ptr_data<T, out_bound_const_ref_triplet<T> > trie;
		typedef trie_with_ptr_data_string<T, out_bound_const_ref_triplet<T> > name_string;
		typedef typename name_string::const_ref name_string_const_ref;

		name_string_const_ref name;
		bool left;
		bool right;

		out_bound(name_string_const_ref name_, bool left_, bool right_);
		out_bound(const out_bound &ob);
		bool operator< (const out_bound &ob) const;
		bool operator== (const out_bound &ob);
	};

    %nodefaultctor out_bound_const_ref_triplet;
    %nodefaultdtor out_bound_ref_triplet;
	template<typename T>
	struct out_bound_const_ref_triplet
    {
		typedef typename out_bound<T>::name_string_const_ref name_string_const_ref;

		out_bound_const_ref_triplet();
		typename out_bound<T>::const_ref get(name_string_const_ref name, bool left, bool right);
		~out_bound_const_ref_triplet();
    };
}
