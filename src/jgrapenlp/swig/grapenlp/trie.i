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

/* trie.i */
%module trie
%include size_t.i
%include array.i
%{
#include <grapenlp/trie.h>
namespace grapenlp
{
    template<typename T>
    using trie_string = typename ::grapenlp::trie<T>::string;

    template<typename T>
    using trie_const_iterator = typename ::grapenlp::trie<T>::const_iterator;
}
%}

namespace grapenlp
{
    %nodefaultctor trie_string;
    %nodefaultdtor trie_string;
    template<typename T>
    class trie_string
    {
    public:
        typename trie<T>::size_type size() const;
        array<T>& to_array(array<T>& a);
        T back() const;
    };

    template<typename T>
    class trie_const_iterator
    {};

    template<typename T>
	class trie
	{
    public:
		typedef std::size_t size_type;

	    trie();
	    ~trie();
    };
}
