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

/* u_set_trie.i */
%module u_set_trie
%include unichar.i
%include set_trie.i
%include u_trie.i
%{
#include <grapenlp/u_set_trie.h>
namespace grapenlp
{
    typedef trie_with_data_string<unichar, bool> u_trie_with_bool_data_string;
    typedef trie_with_data<unichar, bool> u_trie_with_bool_data;

    typedef trie_with_def_data_string<unichar, false_func, false_func::result_type> u_trie_with_def_false_bool_data_string;
	typedef trie_with_def_data<unichar, false_func, false_func::result_type> u_trie_with_def_false_bool_data;

	typedef set_trie<unichar> u_set_trie;
}
%}

namespace grapenlp
{
    typedef ::grapenlp::trie_with_data_string<unichar, ::grapenlp::false_func::result_type> u_trie_with_bool_data_string;
    %template(u_trie_with_bool_data_string) ::grapenlp::trie_with_data_string<unichar, ::grapenlp::false_func::result_type>;
    typedef ::grapenlp::trie_with_data<unichar, ::grapenlp::false_func::result_type> u_trie_with_bool_data;
    %template(u_trie_with_bool_data) ::grapenlp::trie_with_data<unichar, ::grapenlp::false_func::result_type>;

    typedef ::grapenlp::trie_with_def_data_string<unichar, ::grapenlp::false_func, ::grapenlp::false_func::result_type> u_trie_with_def_false_bool_data_string;
    %template(u_trie_with_def_false_bool_data_string) ::grapenlp::trie_with_def_data_string<unichar, ::grapenlp::false_func, ::grapenlp::false_func::result_type>;

	typedef ::grapenlp::trie_with_def_data<unichar, ::grapenlp::false_func, ::grapenlp::false_func::result_type> u_trie_with_def_false_bool_data;
    %template(u_trie_with_def_false_bool_data) ::grapenlp::trie_with_def_data<unichar, ::grapenlp::false_func, ::grapenlp::false_func::result_type>;

	typedef ::grapenlp::set_trie_const_iterator<unichar> u_set_trie_const_iterator;
    %template(u_set_trie_const_iterator) ::grapenlp::set_trie_const_iterator<unichar>;
    SET_TRIE_CONST_ITERATOR_EXTEND(u_set_trie_const_iterator, unichar);

	typedef ::grapenlp::set_trie<unichar> u_set_trie;
    %template(u_set_trie) ::grapenlp::set_trie<unichar>;
    SET_TRIE_EXTEND(u_set_trie, unichar);
}

%inline %{
    grapenlp::u_trie_with_def_false_bool_data_string& u_set_trie_string_deref(grapenlp::u_trie_with_def_false_bool_data_string *s)
    { return *s; }
%}
