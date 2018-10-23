/*
 * GRAPENLP
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

/* u_out_bound.i */
%module u_out_bound
%include u_trie.i
%include out_bound.i
%{
#include <grapenlp/u_out_bound.h>

namespace grapenlp
{
    typedef trie_with_data_string<unichar, out_bound_const_ref_triplet<unichar> *> base_u_out_bound_name_string;
    typedef trie_with_data<unichar, out_bound_const_ref_triplet<unichar> *> base_u_out_bound_trie;
    typedef trie_with_ptr_data_string<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> > u_out_bound_name_string;
    typedef trie_with_ptr_data<unichar, out_bound_const_ref_triplet<unichar> > u_out_bound_trie;
}
%}

namespace grapenlp
{
	typedef ::grapenlp::out_bound<unichar> u_out_bound;
	typedef ::grapenlp::out_bound_const_ref_triplet<unichar> u_out_bound_const_ref_triplet;

    %template(u_out_bound) ::grapenlp::out_bound<unichar>;
    %template(u_out_bound_const_ref_triplet) ::grapenlp::out_bound_const_ref_triplet<unichar>;

    typedef ::grapenlp::trie_with_data_string<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> *> base_u_out_bound_name_string;
    %template(base_u_out_bound_name_string) ::grapenlp::trie_with_data_string<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> *>;
    typedef ::grapenlp::trie_with_data<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> *> base_u_out_bound_trie;
    %template(base_u_out_bound_trie) ::grapenlp::trie_with_data<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> *>;

    typedef ::grapenlp::trie_with_ptr_data_string<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> > u_out_bound_name_string;
    %template(u_out_bound_name_string) ::grapenlp::trie_with_ptr_data_string<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> >;
    typedef ::grapenlp::trie_with_ptr_data<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> > u_out_bound_trie;
    %template(u_out_bound_trie) ::grapenlp::trie_with_ptr_data<unichar, ::grapenlp::out_bound_const_ref_triplet<unichar> >;
}
/*
%{
namespace swig {
    template <> struct traits<grapenlp::u_out_bound_name_string>
    {
        typedef pointer_category category;
        static const char* type_name()
        {
            return "grapenlp::u_out_bound_name_string";
        }
    };
}
%}
*/
