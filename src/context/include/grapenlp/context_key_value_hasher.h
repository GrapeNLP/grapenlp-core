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

#ifndef GRAPENLP_CONTEXT_ITEM_HASHER_H
#define GRAPENLP_CONTEXT_ITEM_HASHER_H

#include <grapenlp/trie_perfect_hasher.h>

namespace grapenlp
{
    /**
     * A pair of perfect hashing indexers, one for context keys and another for context values
     */
    template<typename CharT>
    struct context_key_value_hasher
    {
        typedef trie_perfect_hasher<CharT> hasher;
        typedef typename hasher::hash_type hash_type;
        typedef typename trie_perfect_hasher<CharT>::hash_trie_string_const_ref hash_trie_string_const_ref;

        hasher key_hasher;
        hasher value_hasher;

        context_key_value_hasher(): key_hasher(), value_hasher()
        {}

        void clear()
        {
            key_hasher.clear();
            value_hasher.clear();
        }

        ~context_key_value_hasher()
        {}
    };
} //namespace grapenlp

#endif //GRAPENLP_CONTEXT_ITEM_HASHER_H
