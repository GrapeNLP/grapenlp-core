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

/* inf_delaf.i */
%module inf_delaf
%include vector.i
%include std_set.i
%include u_set_trie.i
%include iterable.i

%{
#include <grapenlp/inf_delaf.h>
namespace grapenlp
{
    typedef typename ::grapenlp::inf_delaf::entry inf_delaf_entry;
    typedef std::vector<inf_delaf_entry*, std::allocator<inf_delaf_entry*> > base_inf_delaf_ambiguous_entry;
    typedef ptr_vector<inf_delaf_entry> inf_delaf_ambiguous_entry;
    typedef const inf_delaf_ambiguous_entry const_inf_delaf_ambiguous_entry;
    typedef std::set<u_trie_with_def_false_bool_data_string*> ust_set;
}
%}

namespace grapenlp
{
    typedef typename ::grapenlp::inf_delaf::entry inf_delaf_entry;
    typedef ::std::vector<inf_delaf_entry*, std::allocator<inf_delaf_entry*> > base_inf_delaf_ambiguous_entry;
    typedef ::grapenlp::ptr_vector<inf_delaf_entry> inf_delaf_ambiguous_entry;
    typedef const ::grapenlp::inf_delaf_ambiguous_entry const_inf_delaf_ambiguous_entry;
    typedef ::std::set<::grapenlp::u_trie_with_def_false_bool_data_string*> ust_set;

    %nodefaultctor inf_delaf_entry;
    %nodefaultdtor inf_delaf_entry;
    struct inf_delaf_entry
    {
    %immutable;
        ust_set semantic_traits;
    %mutable;
    };
}

%template(ust_set) std::set<::grapenlp::u_trie_with_def_false_bool_data_string*>;
%inline %{
    std::set<::grapenlp::u_trie_with_def_false_bool_data_string*>& ust_set_deref(std::set< grapenlp::u_trie_with_def_false_bool_data_string*> *s)
    { return *s; }
%}

%template(base_inf_delaf_ambiguous_entry) ::std::vector<::grapenlp::inf_delaf_entry*, std::allocator<::grapenlp::inf_delaf_entry*> >;
%template(inf_delaf_ambiguous_entry) ::grapenlp::ptr_vector<::grapenlp::inf_delaf_entry, std::allocator<::grapenlp::inf_delaf_entry*> >;

%{
namespace swig {
    template <> struct traits<grapenlp::u_trie_with_def_false_bool_data_string>
    {
        typedef pointer_category category;
        static const char* type_name()
        {
            return "grapenlp::u_trie_with_def_false_bool_data_string";
        }
    };
}
%}
