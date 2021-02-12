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

/* trie_with_data.i */
%module trie_with_data
%include trie.i
%{
#include <grapenlp/trie_with_data.h>
namespace grapenlp
{
    template<typename T, typename Data>
    using trie_with_data_string = typename ::grapenlp::trie_with_data<T, Data>::string;

    template<typename T, typename Data>
    using trie_with_data_const_iterator = typename ::grapenlp::trie_with_data<T, Data>::const_iterator;
}
%}

namespace grapenlp
{
    %nodefaultctor trie_with_data_string;
    %nodefaultdtor trie_with_data_string;
    template<typename T, typename Data>
    class trie_with_data_string: public trie_string<T>
    {
    public:
        Data data;
    };

    template<typename T, typename Data>
    class trie_with_data_const_iterator: public trie_const_iterator<T>
    {};

    template<typename T, typename Data>
	class trie_with_data: public trie<T>
	{
	public:
	    trie_with_data();
	    ~trie_with_data();
	};
}
