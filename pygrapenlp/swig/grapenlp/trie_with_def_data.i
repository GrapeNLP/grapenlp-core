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

/* trie_with_def_data.i */
%module trie_with_def_data
%include trie_with_data.i
%{
namespace grapenlp
{
    template<typename T, typename DefDataValueGetter, typename Data = typename DefDataValueGetter::result_type>
    using trie_with_def_data_string = typename ::grapenlp::trie_with_def_data<T, DefDataValueGetter, Data>::string;

    template<typename T, typename DefDataValueGetter, typename Data = typename DefDataValueGetter::result_type>
    using trie_with_def_data_const_iterator = typename ::grapenlp::trie_with_def_data<T, DefDataValueGetter, Data>::const_iterator;
}
%}

namespace grapenlp
{
    %nodefaultctor trie_with_def_data_string;
    %nodefaultdtor trie_with_def_data_string;
    template<typename T, typename DefDataValueGetter, typename Data = typename DefDataValueGetter::result_type>
    class trie_with_def_data_string: public trie_with_data_string<T, Data>
    {};

    template<typename T, typename DefDataValueGetter, typename Data = typename DefDataValueGetter::result_type>
    class trie_with_def_data_const_iterator: public trie_with_data_const_iterator<T, Data>
    {};

    template<typename T, typename DefDataValueGetter, typename Data = typename DefDataValueGetter::result_type>
    class trie_with_def_data: public trie_with_data<T, Data>
    {
    public:
        trie_with_def_data();
        ~trie_with_def_data();
    };
}
